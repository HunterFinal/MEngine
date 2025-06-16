#pragma once

#ifndef _ME_APP_ABSTRACT_APPLICATION_
#define _ME_APP_ABSTRACT_APPLICATION_

#include "Macro/ApplicationDefines.h"
#include "APP_Generic/ApplicationEventHandler.h"
#include "Misc/NonCopyable.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MAbstractApplicationWindow;
    struct MWindowDefinition;
    
    class MAbstractApplication : public MNonCopyable
    {
      public:
        APP_API explicit MAbstractApplication();
        APP_API virtual ~MAbstractApplication() = default;

        APP_API virtual void PeekMessages() = 0;
        APP_API virtual void UpdateApplication(IN const float DeltaTime) = 0;
        APP_API virtual void ProcessDeferredMessages() = 0;

        APP_API virtual std::shared_ptr<MAbstractApplicationWindow> CreateApplicationWindow() = 0;
        APP_API virtual void InitializeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                              IN const MWindowDefinition& WindowDefinition,
                                              IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow) = 0;
        APP_API virtual void TerminateApplication() = 0;

        APP_API void SetEventHandler(IN const std::shared_ptr<MApplicationEventHandler>& EventHandler);
        APP_API std::shared_ptr<MApplicationEventHandler> GetEventHandler() const;

      private:
        std::shared_ptr<MApplicationEventHandler> m_eventHandler;
        
    };
  }
}

#endif // _ME_APP_ABSTRACT_APPLICATION_