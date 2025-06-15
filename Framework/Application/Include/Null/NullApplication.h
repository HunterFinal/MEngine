#pragma once

#ifndef _ME_APPLICATION_NULL_APPLICATION_
#define _ME_APPLICATION_NULL_APPLICATION_

#include "APP_Generic/AbstractApplication.h"

#include <vector>

namespace MEngine
{
  namespace Application
  {
    class MNullApplicationWindow;

    class MNullApplication final : public MAbstractApplication
                                 , public std::enable_shared_from_this<MNullApplication>
    {
      public:
        APP_API static std::shared_ptr<MNullApplication> CreateNullApplication();

        APP_API ~MNullApplication() = default;
        APP_API void PeekMessages() override final;
        APP_API void ProcessDeferredMessages() override final;

        APP_API std::shared_ptr<MAbstractApplicationWindow> CreateApplicationWindow() override final;
        APP_API void InitializeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                      IN const MWindowDefinition& WindowDefinition,
                                      IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow) override final;
        APP_API void TerminateApplication() override final;
      private:
        APP_API MNullApplication();

      private:
        std::vector<std::shared_ptr<MNullApplicationWindow>> m_windows;
    };
  }
}

#endif // _ME_APPLICATION_NULL_APPLICATION_