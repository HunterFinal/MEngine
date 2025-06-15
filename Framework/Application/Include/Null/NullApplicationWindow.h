#pragma once

#ifndef _ME_APPLICATION_NULL_WINDOW_
#define _ME_APPLICATION_NULL_WINDOW_

#include "APP_Generic/AbstractApplicationWindow.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MNullApplication;

    class MNullApplicationWindow : public MAbstractApplicationWindow
    {
      public:
        APP_API NODISCARD_MSG("Ignore Windows window created by MNullPlatformWindow::CreateNullWindow()") static std::shared_ptr<MNullApplicationWindow> CreateNullWindow();
        APP_API ~MNullApplicationWindow();
        APP_API void InitializeNullWindow(IN const std::shared_ptr<MNullApplication>& Application,
                                          IN const MWindowDefinition& WindowDefinition,
                                          IN const std::shared_ptr<MNullApplicationWindow>& ParentWindow);

      public:
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

      private:
        APP_API explicit MNullApplicationWindow();

      private:
        std::weak_ptr<MNullApplication> m_applicationInstance;
    };
  }
}

#endif // _ME_APPLICATION_NULL_WINDOW_