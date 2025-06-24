#pragma once

#ifndef _ME_APP_WINDOWS_PLATFORM_APPLICATION_
#define _ME_APP_WINDOWS_PLATFORM_APPLICATION_

#include "APP_Generic/AbstractApplication.h"
#include "Windows/WindowsPlatformApplicationInstance.h"
#include "Windows/WindowsHeaderSet.h"
#include "Delegates/Delegate.h"

#include <vector> 

namespace MEngine
{
  namespace Application
  { 
    class MWindowsPlatformWindow;

    class MWindowsPlatformApplication : public MAbstractApplication
                                      , public std::enable_shared_from_this<MWindowsPlatformApplication>
    {
      public:
        APP_API static std::shared_ptr<MWindowsPlatformApplication> CreateWindowsApplication(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle); 

      /**Start of MAbstractApplication interface */
      #pragma region MAbstractApplication interface
      public:
        APP_API virtual void PeekMessages() override;
        APP_API virtual void UpdateApplication(IN const float DeltaTime) override;
        APP_API virtual void ProcessDeferredMessages() override;

        APP_API virtual std::shared_ptr<MAbstractApplicationWindow> CreateApplicationWindow() override;
        APP_API virtual void InitializeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                              IN const MWindowDefinition& WindowDefinition,
                                              IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow) override;
        APP_API virtual void TerminateApplication() override;
      #pragma endregion MAbstractApplication interface
      /**End of MAbstractApplication interface */

      private:
        APP_API static bool WindowsApplicationRegisterClass(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle);
        APP_API static LRESULT CALLBACK ApplicationMessageRouter(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam);
      
      protected:
        APP_API virtual LRESULT CALLBACK ProcessWindowsMessage(IN HWND Hwnd, IN uint32 Msg, IN WPARAM WParam, IN LPARAM LParam);

      private:
        APP_API MWindowsPlatformApplication(IN const HINSTANCE InstanceHandle, IN const HICON IconHandle);

      private:
        std::shared_ptr<ApplicationInstance> m_applicationInstance;
        std::vector<std::shared_ptr<MWindowsPlatformWindow>> m_windows;
    };
  }
}

#endif // _ME_APP_WINDOWS_PLATFORM_APPLICATION_