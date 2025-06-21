#include "Windows/WindowsPlatformApplication.h"

#include "APP_Generic/ApplicationEventHandler.h"
#include "Containers/KeyCharContainer.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "Macro/AssertionMacros.h"
#include "Windows/WindowsPlatformWindow.h"

#include "Globals/CoreGlobals.h"

// Internal
#include "Internal/EventBuilders/KeyCharContainerBuilder.h"


#include <iostream>

namespace
{
  // WARN Temp value before self-defines cursor finish
  constexpr bool g_bUseWin32Cursor = true;

  /**
   * Find current window by HWND
   */
  std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> FindWindowByHWND(
    IN const std::vector<std::shared_ptr<MEngine::Application::MWindowsPlatformWindow>>& WindowsToFind, 
    IN const WindowHandle& Handle
  );

  /**
   * Create OnKeyChar variable on Windows platform
   */
  const MEngine::Application::MKeyCharContainer ConvertToKeyCharContainer(IN WPARAM WParam, IN LPARAM LParam);
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

    void MWindowsPlatformApplication::UpdateApplication(IN const float DeltaTime)
    {
      // Disable unreferenced warning
      (void)DeltaTime;
      // Empty implementation
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
      OnExitEventHandler.Unbind();
    }
    
    bool MWindowsPlatformApplication::WindowsApplicationRegisterClass(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
    {
      // TODO Replace it with self-define cursor
      auto cursor = g_bUseWin32Cursor ? LoadCursor(InstanceHandle, IDC_ARROW) : NULL;
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
      std::shared_ptr<MWindowsPlatformWindow> currentActiveNativeWindowPtr = FindWindowByHWND(m_windows, MEngine::Application::MWindowsPlatformWindowHandle{Hwnd});
      // stop process message while no windows are registered or found window is invalid
      // ウインドウが登録されていないもしくは無効だった場合止める
      if ((m_windows.size() == 0) || (currentActiveNativeWindowPtr == nullptr)) UNLIKELY
      {
        return DefWindowProc(Hwnd, Msg, WParam, LParam);
      }

      std::shared_ptr<MApplicationEventHandler> eventHandler = GetEventHandler();
      me_assert(eventHandler != nullptr);
      if (eventHandler == nullptr) UNLIKELY
      {
        return DefWindowProc(Hwnd, Msg, WParam, LParam);
      }

      switch (Msg)
      {
        case WM_CHAR:
        {
          const MKeyCharContainer msgKeyCharContainer = ConvertToKeyCharContainer(WParam, LParam);
          // TODO
          eventHandler->OnKeyChar(msgKeyCharContainer);

          TCHAR test[3];
          test[0] = msgKeyCharContainer.Character;
          test[1] = static_cast<TCHAR>('\n');
          test[2] = static_cast<TCHAR>('\0');

          MPlatformLowLevelAccessPort::PlatformPrintDebugString(test);

          // NOTE:Should always handle WM_CHAR, Win32 beeps if WM_CHAR is not handled
          return 0;
        }
        break;

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
        // Mouse move
        case WM_NCMOUSEMOVE:
        case WM_MOUSEMOVE:
        {
          bool mouseMoveResult = eventHandler->OnMouseMove();
          std::cout << "Moving mouse" << std::endl;
          
          return mouseMoveResult ? 0 : 1; 
        }
        break;

        case WM_WINDOWPOSCHANGING:
        {
          std::cout << "Changing Window Pos" << std::endl;
          return 0;
        }
        break;

        case WM_MOVE:
        {
          std::cout << "Moving window" << std::endl;
        }  
        break;

        case WM_CLOSE:
        {
          // TODO
          currentActiveNativeWindowPtr->Destroy();
          auto result = std::remove(m_windows.begin(), m_windows.end(), currentActiveNativeWindowPtr);
          m_windows.erase(result, m_windows.end());
          
          if (m_windows.size() < 1)
          {
            if (OnExitEventHandler.IsBound())
            {
              OnExitEventHandler.Invoke();
            }
          }
        }
        break;
        case WM_DESTROY:
        {
          ::CloseWindow(Hwnd);
          ::PostQuitMessage(0);
        }
        break;
      }

      std::cout << "Default" << std::endl;
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

      // FIXME For template test use.Remove this as fast as possible
      OnExitEventHandler = MDelegate<void()>::CreateStatic(&Globals::RequestApplicationExit);

    }
  }
}

namespace
{
  std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> FindWindowByHWND(
    IN const std::vector<std::shared_ptr<MEngine::Application::MWindowsPlatformWindow>>& WindowsToFind, 
    IN const WindowHandle& Handle
  )
  {
    using namespace MEngine::Application;

    for (size_t i = 0 ; i < WindowsToFind.size(); ++i)
    {
      const std::shared_ptr<MWindowsPlatformWindow>& windowPtr = WindowsToFind[i];
      if ((windowPtr != nullptr) && (windowPtr->GetWindowHandle() == Handle))
      {
        return windowPtr;
      }
    }

    return std::shared_ptr<MWindowsPlatformWindow>{nullptr};
  }

  const MEngine::Application::MKeyCharContainer ConvertToKeyCharContainer(IN WPARAM WParam, IN LPARAM LParam)
  {
    using namespace MEngine::Application;

    const TCHAR character = static_cast<TCHAR>(WParam);
    const uint64 characterCode = static_cast<uint64>(WParam);

    /**
     * LParam bit meanings
     * bit 0~15 indicates current message repeat count
     * bit 29 indicates context code flag(ALT key)
     * 0 for ALT was up, 1 for ALT was down
     * bit 30 indicates previous key state flag
     * 0 for new presses, 1 for repeat
     * bit 31 indicates key transition state flag
     * 0 for key pressed, 1 for key released
     */
    // URL: https://learn.microsoft.com/ja-jp/windows/win32/inputdev/wm-char
    // URL: https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input
    const uint16 keyRepeatCount = static_cast<uint16>(LOWORD(LParam));
    
    // high-order word of LParam(16~31)
    const WORD keyFlags = HIWORD(LParam);
    const bool bIsAltDown = (keyFlags & KF_ALTDOWN) != 0;
    const bool bIsRepeat = (keyFlags & KF_REPEAT) != 0;
    const bool bIsKeyUp = (keyFlags & KF_UP) != 0;

    return MKeyCharContainerBuilder::GetInstance()
            .Character(character)
            .RepeatCount(keyRepeatCount)
            .CharacterCode(characterCode)
            .AltDownFlag(bIsAltDown)
            .KeyRepeatFlag(bIsRepeat)
            .KeyUpFlag(bIsKeyUp)
            .Build();
  }
}