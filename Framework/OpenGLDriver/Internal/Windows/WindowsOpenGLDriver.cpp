#include "WindowsOpenGLDriver.h"

#include "Macro/AssertionMacros.h"
#include "GenericPlatformOpenGLDriver.h"
#include "PlatformOpenGLDriverGlobals.h"

namespace
{
  bool g_bOpenGLInitialized = false;

  MEngine::OpenGLDrv::MOpenGLDevice* g_currentDevice = nullptr;

  // Dummy Wndproc for dummy window creation use
  static LRESULT GLDummyWndProc(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam);

  // Initialize a pixel format descriptor for the given device handle
  static void GLInitPixelFormat(IN HDC DeviceCtx);

  // Create OpenGL context
  static void GLContextMakeCurrent(IN HDC DeviceCtx, IN HGLRC RenderingCtx);

  // Get OpenGL context version
  // NOTE: Use this before gladLoadGL may cause assertion
  static void GLGetVersionForCoreProfile(OUT int32& OutMajorVersion, OUT int32& OutMinorVersion);

  // Get opengl current context
  static HGLRC CurrentContext();

} // nameless namespace

namespace MEngine
{

namespace OpenGLDrv
{

/**Windows specific OpenGL context */
struct MOpenGLContext
{
  HWND WindowHandle;
  HDC  DeviceCtxHandle;
  HGLRC OpenGLRenderingCtxHandle;

  GLuint FBO; // A framebuffer object that shares between all vertices.
  GLuint VAO; // A vertex array object that shared between all vertices. // WARNING:Figure out why we need only one?
  bool bDestroyWindowOnDispose;
};


// Create a modern opengl context
static void GLCreateModernContext(OUT MOpenGLContext* OutCtx, const int32 MajorVersion, const int32 MinorVersion, HGLRC ParentCtx)
{
  me_assert(wglCreateContextAttribsARB != NULL);
  me_assert(OutCtx != nullptr);
  me_assert(OutCtx->DeviceCtxHandle != nullptr);

  int attribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, MajorVersion,
    WGL_CONTEXT_MINOR_VERSION_ARB, MinorVersion,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
    WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    0
  };

  OutCtx->OpenGLRenderingCtxHandle = wglCreateContextAttribsARB(OutCtx->DeviceCtxHandle, ParentCtx, attribs);
}

// Create a dummy opengl window
static void GLCreateDummyWindow(OUT MOpenGLContext* OutCtx)
{
  me_assert(OutCtx != nullptr);

  const TCHAR dummyWindowName[] = MTEXT("DummyWindow");

  static bool bWindowClassRegistered = false;
  if (!bWindowClassRegistered)
  {
    WNDCLASSEX wc = 
    {
      .cbSize = sizeof(WNDCLASSEX),
      .style = CS_OWNDC,     
      .lpfnWndProc = ::GLDummyWndProc,
      .cbClsExtra = 0,
      .cbWndExtra = 0,
      .hInstance = NULL,
      .hIcon = NULL,
      .hCursor = NULL,
      .hbrBackground = NULL,
      .lpszMenuName = NULL,
      .lpszClassName = dummyWindowName, 
      .hIconSm = NULL,
    };

    ATOM atom = ::RegisterClassEx(&wc);
    me_assert(atom);
    
    bWindowClassRegistered = true;
  }

  int32 winX = 0;
  int32 winY = 0;
  // Create dummy window
  OutCtx->WindowHandle = ::CreateWindowEx(
                                          WS_EX_OVERLAPPEDWINDOW, 
                                          dummyWindowName,
                                          NULL,
                                          WS_POPUP,                
                                          winX,
                                          winY,
                                          1,    // Dummy width
                                          1,    // Dummy height
                                          NULL,
                                          NULL,
                                          NULL,
                                          NULL
                                         );

  me_assert(OutCtx->WindowHandle != NULL);
  // Destroy dummy window when ctx was disposed
  OutCtx->bDestroyWindowOnDispose = true;

  // Get device ctx
  OutCtx->DeviceCtxHandle = ::GetDC(OutCtx->WindowHandle);
  me_assert(OutCtx->DeviceCtxHandle != NULL);
  GLInitPixelFormat(OutCtx->DeviceCtxHandle);                                       
}

/**Windows specific OpenGL device */
struct MOpenGLDevice
{
  MOpenGLContext RenderingContext;

  MOpenGLDevice()
  {
    // Set this device as the single global device
    me_assert(g_currentDevice != nullptr);
    g_currentDevice = this;

    // Initialize opengl context
    GLCreateDummyWindow(&RenderingContext);

    int32 majorVer = 0;
    int32 minorVer = 0;
    GLGetVersionForCoreProfile(majorVer, minorVer);
    GLCreateModernContext(&RenderingContext, majorVer, minorVer, NULL);
    GLContextMakeCurrent(RenderingContext.DeviceCtxHandle, RenderingContext.OpenGLRenderingCtxHandle);

    me_assert(RenderingContext.OpenGLRenderingCtxHandle != NULL);

    glGenVertexArrays(1, &RenderingContext.VAO);
    glBindVertexArray(RenderingContext.VAO);
    glGenFramebuffers(1, &RenderingContext.FBO);

    GLSetupDefaultContextState();
  }
};

// Implementation of global function declares in GenericPlatformOpenGLDriver.h
bool InitOpenGL()
{
  static bool s_bOpenGLSupported = false;
  if (!g_bOpenGLInitialized)
  {
    // 1. Create dummy OpenGL context for extension initialization
    // Create dummy window 
    MOpenGLContext dummyCtx{};
    GLCreateDummyWindow(&dummyCtx);
  
    // Create OpenGL context
    dummyCtx.OpenGLRenderingCtxHandle = wglCreateContext(dummyCtx.DeviceCtxHandle);
    GLContextMakeCurrent(dummyCtx.DeviceCtxHandle, dummyCtx.OpenGLRenderingCtxHandle);
    
    // Initialize extension functions
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
    wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));

    // Load glad
    ::gladLoadGL();

    // If supported (OpenGL 3.0+)
    if (wglCreateContextAttribsARB != NULL)
    {
      int32 majorVer = 0;
      int32 minorVer = 0;

      // Temporary unbind current OpenGL context
      GLContextMakeCurrent(NULL, NULL);
      ::wglDeleteContext(dummyCtx.OpenGLRenderingCtxHandle);
      GLGetVersionForCoreProfile(majorVer, minorVer);
      GLCreateModernContext(&dummyCtx, majorVer, minorVer, NULL);
      if (dummyCtx.OpenGLRenderingCtxHandle != NULL)
      {
        s_bOpenGLSupported = true;
        GLContextMakeCurrent(dummyCtx.DeviceCtxHandle, dummyCtx.OpenGLRenderingCtxHandle);

        // Reload glad because we create a new opengl context in GLCreateModernContext
        ::gladLoadGL();
      }
    }

    // NOTE Maybe we will load proc address by ourselves later but we will use glad now
    if (s_bOpenGLSupported)
    {
      // FIXME Do something like glad did
    }

    // Release dummy context
    if (dummyCtx.OpenGLRenderingCtxHandle != NULL)
    {
      GLContextMakeCurrent(NULL, NULL);
      wglDeleteContext(dummyCtx.OpenGLRenderingCtxHandle);
    }
    ::ReleaseDC(dummyCtx.WindowHandle, dummyCtx.DeviceCtxHandle);
    if (dummyCtx.bDestroyWindowOnDispose)
    {
      ::DestroyWindow(dummyCtx.WindowHandle);
    }
  }

  return s_bOpenGLSupported;
}

MEngine::OpenGLDrv::MOpenGLDevice* CreateOpenGLDevice()
{
  // FIXME
  return nullptr;
}

void DestroyOpenGLDevice(IN MEngine::OpenGLDrv::MOpenGLDevice* Device)
{
  delete Device;
}

MEngine::OpenGLDrv::MOpenGLContext* CreateOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLDevice* Device, IN void* WindowHandle)
{
  // FIXME
  return nullptr;
}

void DestroyOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLContext* Context)
{
  // FIXME
  delete Context;
}

bool GLHasRenderingContext()
{
  return CurrentContext() == g_currentDevice->RenderingContext.OpenGLRenderingCtxHandle;
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine

namespace
{
  // Dummy Wndproc for dummy window creation use
  LRESULT GLDummyWndProc(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam)
  {
    return ::DefWindowProc(Hwnd, Msg, WParam, LParam);
  }

  // Initialize a pixel format descriptor for the given device handle
  void GLInitPixelFormat(IN HDC DeviceCtx)
  {
    me_assert(DeviceCtx != NULL);

    // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor
    // URL:https://blog-s.xchange.jp/archives/289
    PIXELFORMATDESCRIPTOR pfd{};
    // TODO Make this as a global memset use
    // NOTE Example: MemoryHQ::Memset(...);
    ::memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;      // RGBA -> 8-bit * 4 channels
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int32 pixelFormat = ::ChoosePixelFormat(DeviceCtx, &pfd);
    if (pixelFormat == 0 | !::SetPixelFormat(DeviceCtx, pixelFormat, &pfd))
    {
      // TODO Display error log
      return;
    }
  }

  void GLContextMakeCurrent(HDC DeviceCtx, HGLRC RenderingCtx)
  {
    BOOL result = wglMakeCurrent(DeviceCtx, RenderingCtx);
    if (!result)
    {
      result = wglMakeCurrent(NULL, NULL);
    }
    
    me_assert(result);
  }

  void GLGetVersionForCoreProfile(OUT int32& OutMajorVersion, OUT int32& OutMinorVersion)
  { 
    // Make sure glad is initialized
    me_assert(GLVersion.major != 0);
    
    OutMajorVersion = GLVersion.major;
    OutMinorVersion = GLVersion.minor;

  } 

  HGLRC CurrentContext()
  {
    return ::wglGetCurrentContext();
  }

} // nameless namespace

// NOTE CHECK HERE
// Hint from Claude
/**
 *  if (wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(1);  // 1 = 开启 VSync
                                // 0 = 关闭 VSync
                                // -1 = 自适应 VSync（如果支持）
    }

    int pixelAttribs[] = {
      WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
      WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB, 32,
      WGL_DEPTH_BITS_ARB, 24,
      WGL_STENCIL_BITS_ARB, 8,
      WGL_SAMPLE_BUFFERS_ARB, 1,      // 开启 MSAA
      WGL_SAMPLES_ARB, 4,             // 4x MSAA
      0
    };

    int pixelFormat;
    UINT numFormats;
    wglChoosePixelFormatARB(hDC, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats);
 * 
 */