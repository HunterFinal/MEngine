#include "OpenGLViewport.h"
#include "GenericPlatformOpenGLDriver.h"

namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLViewport::MOpenGLViewport(IN void* WindowHandle, IN uint32 Width, IN uint32 Height)
  : m_GLContext{nullptr}
  , m_width{0}
  , m_height{0}
{
  me_assert(WindowHandle != nullptr);

  MOpenGLRHIBackend& GLBackend = GetGLBackend();

  MOpenGLDevice* device = GLBackend.GetGLDevice();
  me_assert(device != nullptr);

  m_GLContext = MEngine::OpenGLDrv::CreateOpenGLContext(device, WindowHandle);
  Resize(Width, Height);
}

MOpenGLViewport::~MOpenGLViewport()
{
  OPENGL_STATE_CHECK();

  MEngine::OpenGLDrv::DestroyOpenGLContext(m_GLContext);
  m_GLContext = nullptr;
}

void* MOpenGLViewport::GetNativeWindowHandle() const
{
  return MEngine::OpenGLDrv::GetNativeWindow(m_GLContext);
}

void MOpenGLViewport::Resize(IN uint32 NewWidth, IN uint32 NewHeight)
{
  
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine