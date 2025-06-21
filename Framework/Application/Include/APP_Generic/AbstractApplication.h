#pragma once

#ifndef _ME_APP_ABSTRACT_APPLICATION_
#define _ME_APP_ABSTRACT_APPLICATION_

#include "Macro/ApplicationDefines.h"
#include "Misc/NonCopyable.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MAbstractApplicationWindow;
    class MAbstractCursor;
    struct MWindowDefinition;
    struct MApplicationEventHandler;
    
    class MAbstractApplication : public MNonCopyable
    {
      public:
        APP_API explicit MAbstractApplication(/*IN const std::shared_ptr<MAbstractCursor>& Cursor*/);
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
        APP_API const std::shared_ptr<MApplicationEventHandler> GetEventHandler() const;

        APP_API const std::shared_ptr<MAbstractCursor> GetCursor() const;

      private:
        std::shared_ptr<MApplicationEventHandler> m_eventHandler;
        std::shared_ptr<MAbstractCursor> m_cursor;
        
    };
  }
}

#endif // _ME_APP_ABSTRACT_APPLICATION_