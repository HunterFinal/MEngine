#pragma once

#ifndef _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_
#define _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_

#include "FutureFlexCore/FutureFlexCoreAPI.h"
#include "Misc/CoreDefines.h"
#include "Misc/NonCopyable.h"
#include "APP_Generic/ApplicationEventHandler.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MAbstractApplication;
  }
}

namespace MEngine
{
  namespace FutureFlex
  {
    using MEngine::Application::MApplicationEventHandler;
    using MEngine::Application::MAbstractApplication;
    /**
     * MEngine Future Flex UI Application
     */
    class MFutureFlexApplication : public MApplicationEventHandler
                                 , public MNonCopyable
    {
      public:
        RUNTIME_API virtual ~MFutureFlexApplication();

        RUNTIME_API static void Initialize();
        RUNTIME_API static void Initialize(IN const std::shared_ptr<MAbstractApplication>& PlatformApplication);
        RUNTIME_API static bool IsInitialized();
        RUNTIME_API static void Terminate();
        RUNTIME_API static MFutureFlexApplication& GetInstance();

        RUNTIME_API void Update();

        /**Start of MApplicationEventHandler interface */
        #pragma region MApplicationEventHandler interface
        RUNTIME_API virtual bool OnKeyDown() override;
        RUNTIME_API virtual bool OnKeyUp() override;
        RUNTIME_API virtual bool OnMouseDown() override;
        RUNTIME_API virtual bool OnMouseUp() override;
        RUNTIME_API virtual bool OnMouseMove() override;
        #pragma endregion MApplicationEventHandler interface
        /**End of MApplicationEventHandler interface */

      private:
        RUNTIME_API MFutureFlexApplication();
        RUNTIME_API void OnTerminateFFApp();

      private:
        RUNTIME_API static std::shared_ptr<MFutureFlexApplication> s_curtAppInstance;
        RUNTIME_API static std::shared_ptr<MAbstractApplication> s_platformApp; 
    };
  }
}

#endif // _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_