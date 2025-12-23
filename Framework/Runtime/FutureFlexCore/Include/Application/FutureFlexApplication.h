#pragma once

#ifndef _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_
#define _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_

#include "CoreDefines.h"
#include "FutureFlexCoreDefines.h"
#include "APP_Generic/ApplicationEventHandler.h"
#include "Delegates/Delegate.h"
#include "Misc/NonCopyable.h"

#include <memory>
#include <vector>
#include <unordered_set>

// Forward declaration
namespace MEngine
{
  namespace Application
  {
    class MAbstractApplication;
  }

  namespace FutureFlex
  {
    class FFWindow;
  }
}

// Shorten namespace
using MEngine::Application::MApplicationEventHandler;
using MEngine::Application::MAbstractApplication;
using MEngine::Application::MAbstractApplicationWindow;
using MEngine::Application::MKeyInputInfoContainer;
using MEngine::Application::MKeyCharContainer;

namespace MEngine
{
  namespace FutureFlex
  {

    /**
     * MEngine Future Flex UI Application
     */
    class MFutureFlexApplication : public MApplicationEventHandler
                                 , public MNonCopyable
    {
      public:
        FUTUREFLEXCORE_API virtual ~MFutureFlexApplication();
        FUTUREFLEXCORE_API static MFutureFlexApplication& GetInstance();

        FUTUREFLEXCORE_API static void Initialize();
        FUTUREFLEXCORE_API static void Initialize(IN const std::shared_ptr<MAbstractApplication>& PlatformApplication);
        FUTUREFLEXCORE_API static bool IsInitialized();
        FUTUREFLEXCORE_API static void Terminate();
        
        FUTUREFLEXCORE_API void AddWindow(IN std::shared_ptr<FFWindow> FutureFlexWindow);
        FUTUREFLEXCORE_API void Update();
        FUTUREFLEXCORE_API void RequestDestroyWindow(IN std::shared_ptr<FFWindow> WindowToDestroy);
        
        FUTUREFLEXCORE_API void AssignExitRequestedDelegate(IN const MEngine::Core::MDelegate<void()>& OnExitRequestedDelegate);
        
        /**Start of MApplicationEventHandler interface */
        #pragma region MApplicationEventHandler interface
        FUTUREFLEXCORE_API virtual bool OnKeyDown(IN const MKeyInputInfoContainer& Container) override;
        FUTUREFLEXCORE_API virtual bool OnKeyUp(IN const MKeyInputInfoContainer& Container) override;
        FUTUREFLEXCORE_API virtual bool OnKeyChar(IN const MKeyCharContainer& Container) override;
        FUTUREFLEXCORE_API virtual bool OnMouseDown() override;
        FUTUREFLEXCORE_API virtual bool OnMouseUp() override;
        FUTUREFLEXCORE_API virtual bool OnMouseMove() override;
        FUTUREFLEXCORE_API virtual bool OnCursorSet() override;
        FUTUREFLEXCORE_API virtual void OnWindowCreate(IN const std::shared_ptr<MAbstractApplicationWindow>& PlatformWindow, IN const bool bIsSetFocus) override;
        FUTUREFLEXCORE_API virtual void OnWindowClose(IN const std::shared_ptr<MAbstractApplicationWindow>& PlatformWindow) override;
        
        #pragma endregion MApplicationEventHandler interface
        /**End of MApplicationEventHandler interface */
        
        private:
        FUTUREFLEXCORE_API MFutureFlexApplication();
        
        FUTUREFLEXCORE_API void MakeNativeWindow(IN std::shared_ptr<FFWindow> FutureFlexWindow);
        FUTUREFLEXCORE_API void UpdatePlatform();
        FUTUREFLEXCORE_API void OnTerminateFFApp();
        FUTUREFLEXCORE_API void DestroyAllRequestedWindow();
        FUTUREFLEXCORE_API void DestroyWindowImpl(IN const std::shared_ptr<FFWindow>& DestroyedWindow);

      private:
        FUTUREFLEXCORE_API static std::shared_ptr<MFutureFlexApplication> s_curtAppInstance;
        FUTUREFLEXCORE_API static std::shared_ptr<MAbstractApplication> s_platformApp;
        
        std::vector<std::shared_ptr<FFWindow>> m_relatedWindows;

        std::unordered_set<std::shared_ptr<FFWindow>> m_relatedWindowDestroyQueue;

        // Delegates that handle application exit
        MEngine::Core::MDelegate<void()> m_onExitRequested;

        struct InternalData;
        std::unique_ptr<InternalData> m_pImplData;
    };
  }
}

#endif // _ME_RUNTIME_FUTURE_FLEX_CORE_APPLICATION_