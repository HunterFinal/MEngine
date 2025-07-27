#include "Windows/WindowsPlatformApplication.h"

#include "APP_Generic/ApplicationEventHandler.h"
#include "Containers/KeyCharContainer.h"
#include "Containers/KeyInputInfoContainer.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "Macro/AssertionMacros.h"
#include "Windows/WindowsPlatformWindow.h"
#include "Windows/WindowsPlatformCursor.h"

#include "Globals/CoreGlobals.h"

// Internal
#include "Internal/EventBuilders/KeyCharContainerBuilder.h"
#include "Internal/EventBuilders/KeyInputInfoContainerBuilder.h"


#include <iostream>
#include <algorithm>
#include <ranges>


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
  
  /**
   * Create OnKeyDown/OnKeyUp variable on Windows platform
   */
  const MEngine::Application::MKeyInputInfoContainer ConvertToKeyInputInfoContainer(IN WPARAM WParam, IN LPARAM LParam, OUT uint32& ActualKey);

  const MEngine::Application::MWindowsDeferredMessage MakeDeferredMessage(
    IN const std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> Window,
    IN HWND HWnd,
    IN uint32 Message,
    IN WPARAM WParam,
    IN LPARAM LParam,
    DEFAULT_VAR int32 MouseX = 0,
    DEFAULT_VAR int32 MouseY = 0,
    DEFAULT_VAR int32 MouseIndicatorFlags = 0
  );

  /**
   * Check if current input is Alt+Space
   */
  bool IsAltSpacePressed(IN uint32 Message, IN WPARAM WParam, IN LPARAM LParam);
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
      // TODO Why copy

      // NOTE: Comment from UE
      // This function can be reentered when entering a modal tick loop.
		  // We need to make a copy of the events that need to be processed or we may end up processing the same messages twice 
      // NOTE: End comment from UE
      std::vector<MWindowsDeferredMessage> messagesToProcess(m_deferredMsgQueue);

      m_deferredMsgQueue.clear();
      m_deferredMsgQueue.shrink_to_fit();

      for (const auto& message : messagesToProcess)
      {
        ProcessDeferredMessageImpl(message);
      }

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
        // TODO
        // Translated from virtual key message(WM_KEYDOWN)
        // NOTE:Deffered Msg
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

        case WM_SYSCHAR:
        {
          if (!IsAltSpacePressed(Msg, WParam, LParam))
          {
            // Handle this message ourselves except Alt+Space
            return 0;
          }

          // Let Alt+Space pass through and open the window system menu
        }
        break;

        case WM_SYSKEYDOWN:
        {
          // Alt+F4 pressed
          if (WParam == VK_F4)
          {
            // Allow to close window
            // TODO Need some message
            // FIXME Print through output device
            MPlatformLowLevelAccessPort::PlatformPrintDebugString(MTEXT("Alt + F4 pressed"));
          }
          // Alt + Space pressed
          else if (IsAltSpacePressed(Msg, WParam, LParam))
          {
            // Empty implementation
          }
          // Handle other input
          else
          {
            RegisterDeferredMessage(MakeDeferredMessage(currentActiveNativeWindowPtr, Hwnd, Msg, WParam, LParam));
          }
        }
        break;

        // Mouse Cursor
        case WM_SETCURSOR:
        {
          // Sent to a window if the mouse causes the cursor to move within a window and mouse input is not captured.
          // URL: https://learn.microsoft.com/ja-jp/windows/win32/menurc/wm-setcursor

          return eventHandler->OnCursorSet() ? 1 : 0;
        }
        break;

        // Raw Input(Only handle mouse move)
        case WM_INPUT:
        {
          // NOTE:For high precision device use
          // FIXME Start from here!!!!!!!!!!!!!!!!!!!!
          //#error "Start from here"
          // Capture input data immediately, or it will expire if capture it in ProcessDeferredMessages()
          
        }
        break;

        // NOTE:Deffered Msg
        case WM_KEYDOWN:
        {
          RegisterDeferredMessage(MakeDeferredMessage(currentActiveNativeWindowPtr, Hwnd, Msg, WParam, LParam));
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

        // Do nothing when WM_CREATE received
        case WM_CREATE:
        {
          return 0;
        }
        break;

        case WM_PAINT:
        {
          // TODO Add eventHandler paint implementation
          // such as eventHandler->OnPlatformPaint(windowPtr);
        }
        break;

        case WM_ERASEBKGND:
        {
          // Stop background erasing to avoid window flicker
          // return non-zero to indicate don't erase background for us
          // URL: https://learn.microsoft.com/ja-jp/windows/win32/winmsg/wm-erasebkgnd
          return 1;
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
          eventHandler->OnWindowClose(currentActiveNativeWindowPtr);

          return 0;
        }
        break;
        case WM_DESTROY:
        {
          // TODO make this as a helper function
          auto [removeItrBegin, removeItrEnd] = std::ranges::remove(m_windows, currentActiveNativeWindowPtr);
          m_windows.erase(removeItrBegin, m_windows.end());

          return 0;
        }
        break;
      }

      std::cout << "Default" << std::endl;
      return DefWindowProc(Hwnd, Msg, WParam, LParam);
    }

    MWindowsPlatformApplication::MWindowsPlatformApplication(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
      : MAbstractApplication(std::make_shared<MWindowsPlatformCursor>())
      , m_applicationInstance{std::make_shared<MWindowsPlatformApplicationInstance>(InstanceHandle)}
      , m_windows{}
    {
      // HACK Disable this process from being showing "Ghost UI" during slow tasks
      ::DisableProcessWindowsGhosting();

      const bool bRegisterClassSucceeded = WindowsApplicationRegisterClass(InstanceHandle, IconHandle);
      me_assert(bRegisterClassSucceeded);

    }

    void MWindowsPlatformApplication::RegisterDeferredMessage(IN const MWindowsDeferredMessage& DeferredMessage)
    {
      if (Globals::GIsPeekingMessagesOutsideOfMainLoop)
      {
        m_deferredMsgQueue.emplace_back(DeferredMessage);
      }
      else
      {
        // process it immediately if it isn't deferring message
        ProcessDeferredMessageImpl(DeferredMessage);
      }
    }

    uint32 MWindowsPlatformApplication::ProcessDeferredMessageImpl(IN const MWindowsDeferredMessage& Message)
    {
      // Finish process if there's no avaliable window left
      if ((m_windows.size() == 0) || Message.NativeWindowWeakPtr.expired()) UNLIKELY
      {
        return 0;
      }

      std::shared_ptr<MApplicationEventHandler> eventHandler = GetEventHandler();
      me_assert(eventHandler != nullptr);

      HWND hWnd = Message.HWnd;
      uint32 msg = Message.Message;
      WPARAM wParam = Message.WParam;
      LPARAM lParam = Message.LParam;

      std::shared_ptr<MWindowsPlatformWindow> currentActiveNativeWindowPtr = Message.NativeWindowWeakPtr.lock();

      switch(msg)
      {
        // Key down
        // URL: https://learn.microsoft.com/ja-jp/windows/win32/inputdev/wm-syskeydown
        // URL: https://learn.microsoft.com/ja-jp/windows/win32/inputdev/wm-keydown
        // URL: https://learn.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
          uint32 actualKey = 0;
          const MEngine::Application::MKeyInputInfoContainer msgKeyInputInfoContainer = ConvertToKeyInputInfoContainer(wParam, lParam, actualKey);

          const bool result = eventHandler->OnKeyDown(msgKeyInputInfoContainer);

          // Always handle key down message to avoid beep sound
          if (result || (msg != WM_SYSKEYDOWN))
          {
            return 0;
          }
        }
        break;
      }
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
    using MEngine::Application::MKeyCharContainerBuilder;
    using MEngine::Application::MKeyCharContainer;

    const TCHAR character = static_cast<TCHAR>(WParam);
    // TODO WPARAM is uint64 in 64-bit and uint32 in 32-bit
    // TODO It seems to be safe
    const uint32 characterCode = static_cast<uint32>(WParam);

    /**
     * LParam bit meanings about message WM_CHAR
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

  const MEngine::Application::MKeyInputInfoContainer ConvertToKeyInputInfoContainer(IN WPARAM WParam, IN LPARAM LParam, OUT uint32& ActualKey)
  {

    using MEngine::Application::MKeyInputInfoContainer;
    using MEngine::Application::MKeyInputInfoContainerBuilder;

    const uint32 win32VKCode = static_cast<uint32>(WParam);
    // Get the character code from virtuak key, If 0, no translation exists
    // URL: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mapvirtualkeyw
    const uint32 characterCode = ::MapVirtualKey(win32VKCode, MAPVK_VK_TO_CHAR);

    const uint16 keyRepeatCount = static_cast<uint16>(LOWORD(LParam));

    // high-order word of LParam(16~31)
    const WORD keyFlags = HIWORD(LParam);
    const bool bIsRepeat = (keyFlags & KF_REPEAT) != 0;

    // FIXME Need implementation immediately
    // low-order byte of keyFlags(16~23)
    WORD scanCode = LOBYTE(keyFlags);
    if ((keyFlags & KF_EXTENDED) != 0)
    {
      scanCode = MAKEWORD(scanCode, 0xE0);
    }

    ActualKey = win32VKCode;

    // FIXME Need implementation
    switch (win32VKCode)
    {
      case VK_SHIFT:
      {
        ActualKey = LOWORD(::MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX));
      }
      break;

      case VK_CONTROL:
      {
        ActualKey = LOWORD(::MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX));
      }
      break;

      case VK_MENU:
      {
        ActualKey = LOWORD(::MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX));
      }
      break;

      case VK_CAPITAL:
      {

      }
      break;
    }

    // TODO
    return MKeyInputInfoContainerBuilder::GetInstance()
            .ActualKeyCode(ActualKey)
            .CharacterCode(characterCode)
            .RepeatCount(keyRepeatCount)
            .KeyRepeatFlag(bIsRepeat)
            .Build();

  }

  bool IsAltSpacePressed(IN uint32 Message, IN WPARAM WParam, IN LPARAM LParam)
  {
    // Only accept following messages 
    switch(Message)
    {
      case WM_SYSCHAR:
      {
        const bool bIsAltDown = (HIWORD(LParam) & KF_ALTDOWN) != 0;
        const bool bIsSpaceDown = (WParam == VK_SPACE);

        return bIsAltDown && bIsSpaceDown;
      }
      break;
    }

    return false;
  }

  const MEngine::Application::MWindowsDeferredMessage MakeDeferredMessage(
    IN const std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> Window,
    IN HWND HWnd,
    IN uint32 Message,
    IN WPARAM WParam,
    IN LPARAM LParam,
    DEFAULT_VAR int32 MouseX,
    DEFAULT_VAR int32 MouseY,
    DEFAULT_VAR int32 MouseIndicatorFlags
  )
  {
    return MEngine::Application::MWindowsDeferredMessage
    {
      .NativeWindowWeakPtr = Window,
      .HWnd = HWnd,
      .Message = Message,
      .WParam = WParam,
      .LParam = LParam,
      .MouseX = MouseX,
      .MouseY = MouseY,
      .MouseIndicatorFlags = MouseIndicatorFlags
    };
  }
}