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
#include "Internal/EventBuilders/Windows/WindowsDeferredMessageBuilder.h"
#include "Internal/Windows/WindowsDeferredMessage.h"

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
    IN LPARAM LParam
  );

  const MEngine::Application::MWindowsDeferredMessage MakeDeferredMessage_Mouse(
    IN const std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> Window,
    IN HWND HWnd,
    IN uint32 Message,
    IN WPARAM WParam,
    IN LPARAM LParam,
    IN int32 MouseX,
    IN int32 MouseY,
    IN int32 MouseIndicatorFlags   
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
    enum EWinModifierKeyType : uint8
    {
      Win_LeftShift = 0,    // VK_LSHIFT
      Win_RightShift = 1,   // VK_RSHIFT
      Win_LeftControl = 2,  // VK_LCONTROL
      Win_RightControl = 3, // VK_RCONTROL
      Win_LeftAlt = 4,      // VK_LMENU
      Win_RightAlt = 5,     // VK_RMENU
      Win_CapsLock = 6,     // VK_CAPITAL

      Count,
    };

    struct MWindowsPlatformApplication::InternalData
    {
      std::vector<MWindowsDeferredMessage> DeferredMsgQueue;

      POINT PreviousCursorPoint;

      bool ModifierKeysState[EWinModifierKeyType::Count];
    };

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
      
      // NOTE: Comment from UE
      // This function can be reentered when entering a modal tick loop.
		  // We need to make a copy of the events that need to be processed or we may end up processing the same messages twice 
      // NOTE: End comment from UE
      
      // TODO Why copy
      std::vector<MWindowsDeferredMessage> messagesToProcess{m_pImplData->DeferredMsgQueue};
      m_pImplData->DeferredMsgQueue.clear();
      m_pImplData->DeferredMsgQueue.shrink_to_fit();

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

    MModifierKeysState MWindowsPlatformApplication::GetModState() const
    {
      const bool bIsLeftShiftPressed = m_pImplData->ModifierKeysState[Win_LeftShift];
      const bool bIsRightShiftPressed = m_pImplData->ModifierKeysState[Win_RightShift];
      const bool bIsLeftControlPressed = m_pImplData->ModifierKeysState[Win_LeftControl];
      const bool bIsRightControlPressed = m_pImplData->ModifierKeysState[Win_RightControl];
      const bool bIsLeftAltPressed = m_pImplData->ModifierKeysState[Win_LeftAlt];
      const bool bIsRightAltPressed = m_pImplData->ModifierKeysState[Win_RightAlt];

      // NOTE
      const bool bAreCapsLocked = m_pImplData->ModifierKeysState[Win_CapsLock];

      return MModifierKeysState
      {
        bIsLeftShiftPressed, bIsRightShiftPressed,
        bIsLeftControlPressed, bIsRightControlPressed,
        bIsLeftAltPressed, bIsRightAltPressed,
        false, false                                  // Windows do not have command keys
      };
    }
    
    bool MWindowsPlatformApplication::WindowsApplicationRegisterClass(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle)
    {
      // TODO Replace it with self-define cursor
      auto cursor = g_bUseWin32Cursor ? LoadCursor(InstanceHandle, IDC_ARROW) : NULL;
      const uint32 wndClassStyle = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

      // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-wndclassexw
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

        // Mouse input event
        // Left button
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        // Right button
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_RBUTTONDBLCLK:
        // Middle button
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MBUTTONDBLCLK:
        // X button
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_XBUTTONDBLCLK:
        // Mouse move
        case WM_MOUSEMOVE:
        case WM_NCMOUSEMOVE:
        // Mouse wheel
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
        {
          RegisterDeferredMessage(MakeDeferredMessage(currentActiveNativeWindowPtr, Hwnd, Msg, WParam, LParam));

          // Handled
          return 0;
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
          // URL https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-getrawinputdata?source=recommendations
          uint32 bufSize = 0;
          (void)::GetRawInputData(reinterpret_cast<HRAWINPUT>(LParam), RID_INPUT, nullptr, &bufSize, sizeof(RAWINPUTHEADER));

          std::vector<uint8> rawData{};
          rawData.resize(bufSize);
          if (::GetRawInputData(reinterpret_cast<HRAWINPUT>(LParam), RID_INPUT, rawData.data(), &bufSize, sizeof(RAWINPUTHEADER)) == bufSize)
          {
            const RAWINPUT* const raw = reinterpret_cast<const RAWINPUT* const>(rawData.data());

            // Handle mouse raw input
            if (raw->header.dwType == RIM_TYPEMOUSE)
            {
              // URL https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-rawmouse
              const bool bIsAbsoluteInput = (raw->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == MOUSE_MOVE_ABSOLUTE;
              if (bIsAbsoluteInput)
              {
                // Get the new cursor point
                POINT cursorPt{};
                
                // Calculate cursor point
                {
                  const bool bIsVirtualDesktop = (raw->data.mouse.usFlags & MOUSE_VIRTUAL_DESKTOP) == MOUSE_VIRTUAL_DESKTOP;
                  // URL https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-rawmouse
                  /**
                   * MOUSE_MOVE_ABSOLUTE 値が指定されている場合は、lLastXとlLastY 0 から 65,535 の間の正規化された絶対座標が含まれます。
                   * 座標(0,0)は、表示サーフェスの左上隅にマップされます。座標(65535,65535)が右下隅にマップされます。
                   * マルチモニターシステムでは、座標はプライマリモニターにマップされます。
                   */
                  const int32 maxAbsoluteCoord = USHRT_MAX;
                  
                  const int32 left = bIsVirtualDesktop ? GetSystemMetrics(SM_XVIRTUALSCREEN) : 0;
                  const int32 right = GetSystemMetrics(bIsVirtualDesktop ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
                  const int32 top = bIsVirtualDesktop ? GetSystemMetrics(SM_YVIRTUALSCREEN) : 0;
                  const int32 bottom = GetSystemMetrics(bIsVirtualDesktop ? SM_CYVIRTUALSCREEN : SM_CXSCREEN);

                  cursorPt.x = static_cast<LONG>(MMath::MulDivF(static_cast<int32>(raw->data.mouse.lLastX), right, maxAbsoluteCoord) + left);
                  cursorPt.y = static_cast<LONG>(MMath::MulDivF(static_cast<int32>(raw->data.mouse.lLastY), bottom, maxAbsoluteCoord) + top);

                  // NOTE Need more information of WM_INPUT
                }
                
              }
              else
              {
                // Raw input is coming in as relative
                // It is likely a traditional mouse device
                const int32 xPosRelative = raw->data.mouse.lLastX;
                const int32 yPosRelative = raw->data.mouse.lLastY;

                RegisterDeferredMessage(MakeDeferredMessage_Mouse(currentActiveNativeWindowPtr, Hwnd, Msg, WParam, LParam, xPosRelative, yPosRelative, MOUSE_MOVE_RELATIVE));
                // Handle ourselves
                return 1;
              }
            }
          }
        }
        break;

        // NOTE:Deffered Msg
        case WM_KEYDOWN:
        {
          RegisterDeferredMessage(MakeDeferredMessage(currentActiveNativeWindowPtr, Hwnd, Msg, WParam, LParam));
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
          if (currentActiveNativeWindowPtr != nullptr)
          {
            eventHandler->OnWindowClose(currentActiveNativeWindowPtr);
          }

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
      , m_pImplData{std::make_unique<MWindowsPlatformApplication::InternalData>()}
    {
      constexpr SIZE_T modifierKeysMemCount = sizeof(decltype(*InternalData::ModifierKeysState)) * static_cast<SIZE_T>(EWinModifierKeyType::Count);
      ::memset(m_pImplData->ModifierKeysState, 0, modifierKeysMemCount);

      // HACK Disable this process from being showing "Ghost UI" during slow tasks
      ::DisableProcessWindowsGhosting();

      const bool bRegisterClassSucceeded = WindowsApplicationRegisterClass(InstanceHandle, IconHandle);
      me_assert(bRegisterClassSucceeded);

    }

    void MWindowsPlatformApplication::RegisterDeferredMessage(IN const MWindowsDeferredMessage& DeferredMessage)
    {
      if (Globals::GIsPeekingMessagesOutsideOfMainLoop)
      {
        m_pImplData->DeferredMsgQueue.emplace_back(DeferredMessage);
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

        // Mouse move
        case WM_MOUSEMOVE:
        case WM_NCMOUSEMOVE:
        {
          const bool result = eventHandler->OnMouseMove();

          return result ? 0 : 1;
        }
        break;
      }

      // Handled
      return 0;
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
    IN LPARAM LParam
  )
  {
    return MEngine::Application::MWindowsDeferredMessageBuilder::Builder()
           .NativeWindow(Window)
           .WindowHandle(HWnd)
           .Message(Message)
           .WParam(WParam)
           .LParam(LParam)
           .Build();
  }

  const MEngine::Application::MWindowsDeferredMessage MakeDeferredMessage_Mouse(
    IN const std::shared_ptr<MEngine::Application::MWindowsPlatformWindow> Window,
    IN HWND HWnd,
    IN uint32 Message,
    IN WPARAM WParam,
    IN LPARAM LParam,
    IN int32 MouseX,
    IN int32 MouseY,
    IN int32 MouseIndicatorFlags   
  )
  {
    return MEngine::Application::MWindowsDeferredMessageBuilder::Builder()
        .NativeWindow(Window)
        .WindowHandle(HWnd)
        .Message(Message)
        .WParam(WParam)
        .LParam(LParam)
        .MouseX(MouseX)
        .MouseY(MouseY)
        .MouseIndicatorFlags(MouseIndicatorFlags)
        .Build();
  }
}