#include "Windows/WindowsHeaderSet.h"
#include "Windows/WindowsPlatformWindow.h"
#include "Math/MEngineMathUtility.h"

#include <cassert>

namespace
{
  constexpr ANSICHAR APP_WINDOW_CLASS_NAME_A[] = "MEngineWindow";
  constexpr WIDECHAR APP_WINDOW_CLASS_NAME_W[] = MTEXT("MEngineWindow");
}

namespace MEngine
{
  namespace Application
  {
    MWindowsPlatformWindow::~MWindowsPlatformWindow()
    {
      m_hwnd.reset();
    }

    std::shared_ptr<MWindowsPlatformWindow> MWindowsPlatformWindow::CreateWindowsWindow()
    {
      return std::shared_ptr<MWindowsPlatformWindow>(new MWindowsPlatformWindow{});
    }

    void MWindowsPlatformWindow::InitializeWindowsWindow( IN const std::shared_ptr<MWindowsPlatformApplication>& Application,
                                                          IN const MWindowDefinition& WindowDefinition,
                                                          IN HINSTANCE ApplicationInstance,
                                                          IN const std::shared_ptr<MWindowsPlatformWindow>& ParentWindow)
    {
      m_definition = WindowDefinition;
      m_owningApplication = Application;

      const float initRectX = m_definition.DesiredPositionOnScreenX;
      const float initRectY = m_definition.DesiredPositionOnScreenY;
      const float initRectWidth = m_definition.DesiredWidthOnScreen;
      const float initRectHeight = m_definition.DesiredHeightOnScreen;

      uint32 windowStyle = WS_OVERLAPPEDWINDOW;// タイトルバーと境界線があるウィンドウ
      uint32 windowEXStyle = 0l;

      int32 windowX = MMath::TruncToInt32(initRectX);
      int32 windowY = MMath::TruncToInt32(initRectY);
      int32 windowWidth = MMath::TruncToInt32(initRectWidth);
      int32 windowHeight = MMath::TruncToInt32(initRectHeight);

      RECT borderRect = { 0l, 0l ,0l ,0l};
      ::AdjustWindowRectEx(&borderRect,  windowStyle, false, windowEXStyle);

      // Border rect size is negative
      windowX += borderRect.left;
      windowY += borderRect.top;
    
      windowWidth += (borderRect.right - borderRect.left);
      windowHeight += (borderRect.bottom - borderRect.top);

      WindowHandle parentHandle = (ParentWindow != nullptr) ? ParentWindow->GetWindowHandle() : WindowHandle{NULL};
      HMENU menuHandle = NULL;
      LPVOID lpParam = static_cast<void*>(m_owningApplication.get());

      // Create window
      HWND hWnd = ::CreateWindowEx(
                                  windowEXStyle, 
                                  ApplicationClassName,
                                  m_definition.Title.c_str(),
                                  windowStyle,                
                                  windowX,
                                  windowY,
                                  windowWidth,
                                  windowHeight,
                                  parentHandle,
                                  menuHandle,
                                  ApplicationInstance,
                                  lpParam
                                );

      if (hWnd == NULL)
      {
        // Capture error context immediatelly after CreateWindowEx
        const uint32 errorCtx = ::GetLastError(); 

        assert(false);
        PLATFORM_BREAK();

        return;
      }

      if (m_hwnd != nullptr)
      {
        m_hwnd.reset();
      }

      m_hwnd = std::make_shared<WindowHandle>(hWnd);

      // uint32 windowPositionFlags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;


    }

    WindowHandle MWindowsPlatformWindow::GetWindowHandle() const
    {
      return (m_hwnd != nullptr) ? *m_hwnd : WindowHandle{NULL};
    }

    void MWindowsPlatformWindow::Destroy()
    {

    }

    void MWindowsPlatformWindow::ResizeWindow(IN int32 NewX, IN int32 NewY, IN uint32 NewWidth, IN uint32 NewHeight)
    {

    }

    void MWindowsPlatformWindow::MoveTo(IN int32 X, IN int32 Y)
    {

    }

    void MWindowsPlatformWindow::Show()
    {

    }

    void MWindowsPlatformWindow::Hide()
    {

    }

    void MWindowsPlatformWindow::Maximize()
    {

    }

    void MWindowsPlatformWindow::Minimize()
    {

    }

    void MWindowsPlatformWindow::Enable()
    {

    }

    void MWindowsPlatformWindow::Disable()
    {

    }

    void MWindowsPlatformWindow::SetTitle(IN const char* Text)
    {

    }

    void MWindowsPlatformWindow::SetWindowMode(IN EWindowMode NewWindowMode)
    {

    }

    bool MWindowsPlatformWindow::IsMaximized() const
    {
      return false;
    }

    bool MWindowsPlatformWindow::IsMinimized() const
    {
      return false;
    }

    MWindowsPlatformWindow::MWindowsPlatformWindow(IN MWindowsPlatformWindow&& Other) noexcept
      : Super(std::move(Other))
      , m_hwnd(std::move(Other.m_hwnd))
    {
      Other.m_hwnd.reset();
    }

    MWindowsPlatformWindow& MWindowsPlatformWindow::operator=(IN MWindowsPlatformWindow&& Other) noexcept
    {
      if (this != &Other)
      {
        m_hwnd.reset();
        m_hwnd = std::move(Other.m_hwnd);

        Other.m_hwnd.reset();
      }

      return *this;
    }

    MWindowsPlatformWindow::MWindowsPlatformWindow()
      : Super()
      , m_hwnd{std::make_shared<WindowHandle>(nullptr)}
    { }

    const char* MWindowsPlatformWindow::GetAppWindowClassA()
    {
      return APP_WINDOW_CLASS_NAME_A;
    }

    const wchar_t* MWindowsPlatformWindow::GetAppWindowClassW()
    {
      return APP_WINDOW_CLASS_NAME_W;
    }
  }
}