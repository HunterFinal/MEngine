#include "Windows/WindowsPlatformApplication.h"
#include "Windows/WindowsPlatformWindow.h"
#include "Windows/WindowsHeaderSet.h"
#include "Macro/AssertionMacros.h"

#include <iostream>

namespace
{
  // WARN Temp value before self-defines cursor finish
  constexpr bool bUseWin32Cursor = true;
}

namespace MEngine
{
  namespace Application
  {
    std::shared_ptr<MWindowsPlatformApplication> MWindowsPlatformApplication::CreateWindowsApplication(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
    {
      // TODO Non thread-safe
      return std::shared_ptr<MWindowsPlatformApplication>(new MWindowsPlatformApplication(InstanceHandle, IconHandle));
    }

    void MWindowsPlatformApplication::PeekMessages()
    {
      MSG Message{};

      if (::PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
      {
        ::TranslateMessage(&Message);
        ::DispatchMessage(&Message);
      }
    }

    void MWindowsPlatformApplication::ProcessDeferredMessages()
    {
      // TODO need implementation
    }

    std::shared_ptr<MAbstractApplicationWindow> MWindowsPlatformApplication::CreateApplicationWindow()
    {
      return MWindowsPlatformWindow::CreateWindowsWindow();
    }

    void MWindowsPlatformApplication::InitializeWindow( IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                                        IN const MWindowDefinition& WindowDefinition,
                                                        IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow)
    {
      me_assert(m_applicationInstance != nullptr);

      std::shared_ptr<MWindowsPlatformWindow> windowsWindow = std::dynamic_pointer_cast<MWindowsPlatformWindow>(Window);
      std::shared_ptr<MWindowsPlatformWindow> parentWindow = std::dynamic_pointer_cast<MWindowsPlatformWindow>(ParentWindow);

      me_assert(windowsWindow != nullptr);
      if (windowsWindow != nullptr)
      {
        // HACK shared_ptrで管理するしか使わないので。使い方を慎重に
        windowsWindow->InitializeWindowsWindow(shared_from_this(), WindowDefinition, *m_applicationInstance, parentWindow);
      }

      m_windows.emplace_back(windowsWindow);
    }

    void MWindowsPlatformApplication::TerminateApplication()
    {
      // TODO need implementation
    }
    
    bool MWindowsPlatformApplication::WindowsApplicationRegisterClass(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
    {
      // TODO Replace it with self-define cursor
      auto cursor = bUseWin32Cursor ? LoadCursor(InstanceHandle, IDC_ARROW) : NULL;
      const uint32 wndClassStyle = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

      WNDCLASSEX wc{
        .cbSize = sizeof(WNDCLASSEX),
        .style = wndClassStyle,
        .lpfnWndProc = ApplicationMessageRouter,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = InstanceHandle,
        .hIcon = IconHandle,
        .hCursor = cursor,
        .hbrBackground = NULL,
        .lpszMenuName = NULL,
        .lpszClassName = ApplicationClassName,    // TODO need change to self-define string
        .hIconSm = NULL,
      };

      if (!::RegisterClassEx(&wc))
      {
        // WARN temp use for debug
        PLATFORM_BREAK();
        return false;
      }

      return true;
    }

    LRESULT MWindowsPlatformApplication::ApplicationMessageRouter(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam)
    {
      MWindowsPlatformApplication* curtAppPtr = nullptr;
      if (Msg == WM_CREATE)
      {
        LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(LParam);
        curtAppPtr = reinterpret_cast<MWindowsPlatformApplication*>(createStruct->lpCreateParams);
        SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(curtAppPtr));
      }
      else
      {
        curtAppPtr = reinterpret_cast<MWindowsPlatformApplication*>(GetWindowLongPtr(Hwnd, GWLP_USERDATA));
      }

      if (curtAppPtr != nullptr)
      {
        return curtAppPtr->ProcessWindowsMessage(Hwnd, Msg, WParam, LParam);
      }
      else
      {
        return DefWindowProc(Hwnd, Msg, WParam, LParam);
      }
    }

    LRESULT MWindowsPlatformApplication::ProcessWindowsMessage(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam)
    {

      switch (Msg)
      {
        case WM_KEYDOWN:
        {
          switch (WParam)
          {
            case VK_ESCAPE:
            {
              PostMessage(Hwnd, WM_CLOSE, 0, 0);
            }
            break;
          }
        }
        break;
        case WM_MOUSEMOVE:
        {
          std::cout << "Moving mouse" << std::endl;
        }
        break;
        case WM_CLOSE:
        {
          ::DestroyWindow(Hwnd);
        }
        break;
        case WM_DESTROY:
        {
          ::CloseWindow(Hwnd);
          ::PostQuitMessage(0);
        }
        break;
      }

      return DefWindowProc(Hwnd, Msg, WParam, LParam);
    }

    MWindowsPlatformApplication::MWindowsPlatformApplication(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
      : MAbstractApplication()
      , m_applicationInstance{std::make_shared<MWindowsPlatformApplicationInstance>(InstanceHandle)}
      , m_windows{}
    {
      // HACK Disable this process from being showing "Ghost UI" during slow tasks
      ::DisableProcessWindowsGhosting();

      const bool bRegisterClassSucceeded = WindowsApplicationRegisterClass(InstanceHandle, IconHandle);
      me_assert(bRegisterClassSucceeded);
    }
  }
}