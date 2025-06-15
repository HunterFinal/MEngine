#pragma once

#ifndef _ME_APP_WINDOWS_PLATFORM_WINDOW_
#define _ME_APP_WINDOWS_PLATFORM_WINDOW_

#include "APP_Generic/AbstractApplicationWindow.h"

#include "Windows/WindowsPlatformApplicationInstance.h"
#include "Windows/WindowsPlatformWindowHandle.h"

#include "Macro/TypeAliasMacro.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MWindowsPlatformApplication;

    class MWindowsPlatformWindow : public MAbstractApplicationWindow
    {
      TYPEDEF(MAbstractApplicationWindow, Super);

      public:
        APP_API virtual ~MWindowsPlatformWindow();

        APP_API NODISCARD_MSG("Ignore Windows window created by MWindowsPlatformWindow::CreateWindowsWindow()") static std::shared_ptr<MWindowsPlatformWindow> CreateWindowsWindow();

        APP_API void InitializeWindowsWindow( IN const std::shared_ptr<MWindowsPlatformApplication>& Application,
                                              IN const MWindowDefinition& WindowDefinition, 
                                              IN HINSTANCE ApplicationInstance,
                                              IN const std::shared_ptr<MWindowsPlatformWindow>& ParentWindow);

        APP_API WindowHandle GetWindowHandle() const;

        // [ ] make cross-platform string immediately
        APP_API static const ANSICHAR* GetAppWindowClassA();
        APP_API static const WIDECHAR* GetAppWindowClassW();

        /**Start of MAbstractWindow interface */
        #pragma region MAbstractWindow interface
        APP_API virtual void Destroy() override;
        APP_API virtual void ResizeWindow(IN int32 NewX, IN int32 NewY, IN uint32 NewWidth, IN uint32 NewHeight) override;
        APP_API virtual void MoveTo(IN int32 X, IN int32 Y) override;
        APP_API virtual void Show() override;
        APP_API virtual void Hide() override;
        APP_API virtual void Maximize() override;
        APP_API virtual void Minimize() override;
        APP_API virtual void Enable() override;
        APP_API virtual void Disable() override;
        APP_API virtual void SetTitle(IN const ANSICHAR* Text) override;
        APP_API virtual void SetWindowMode(IN EWindowMode NewWindowMode) override; 
        APP_API virtual bool IsMaximized() const override;
        APP_API virtual bool IsMinimized() const override;
        #pragma endregion MAbstractWindow interface
        /**End of MAbstractWindow interface */

        APP_API MWindowsPlatformWindow(MWindowsPlatformWindow&& Other) noexcept;
        APP_API MWindowsPlatformWindow& operator=(MWindowsPlatformWindow&& Other) noexcept;

      private:

        APP_API explicit MWindowsPlatformWindow();

      private:
        std::weak_ptr<MWindowsPlatformApplication> m_owningApplication;
        std::shared_ptr<WindowHandle> m_hwnd;
    };

    // TODO Create cross-platform string immediately
    #ifdef UNICODE
      #define ApplicationClassName MWindowsPlatformWindow::GetAppWindowClassW()
    #else
      #define ApplicationClassName MWindowsPlatformWindow::GetAppWindowClassA()
    #endif
  }
}

#endif // _ME_APP_WINDOWS_PLATFORM_WINDOW_