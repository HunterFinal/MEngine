

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
  
  /**
   * @brief The base class of platform-base application
   * 
   * プラットフォームアプリケーションの基底クラス
   */
  class MAbstractApplication : public MNonCopyable
  {
    protected:
      using Super = MEngine::Application::MAbstractApplication;
    
    public:
      APP_API explicit MAbstractApplication(IN const std::shared_ptr<MAbstractCursor>& Cursor);
      APP_API virtual ~MAbstractApplication();
      APP_API void SetEventHandler(IN const std::shared_ptr<MApplicationEventHandler>& EventHandler);

      /**
       * @brief Retrieve platform messages and process them
       */
      APP_API virtual void PeekMessages() = 0;

      /**
       * @brief Update application after PeekMessages is called
       * 
       * @param DeltaTime Time since last frame
       */
      APP_API virtual void UpdateApplication(IN const float DeltaTime) = 0;

      /**
       * @brief Process deferred message that can not handle in PeekMessages
       */
      APP_API virtual void ProcessDeferredMessages() = 0;

      /**
       * @brief Factory method to create specific platform window
       * 
       * @return Pointer of specific platform window 
       */
      APP_API virtual std::shared_ptr<MAbstractApplicationWindow> CreateApplicationWindow() = 0;

      /**
       * @brief Initialize window and add into this platform application
       * 
       * @param Window            Window to initialize
       * @param WindowDefinition  Window definition structure
       * @param ParentWindow      Parent window
       */
      APP_API virtual void InitializeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                            IN const MWindowDefinition& WindowDefinition,
                                            IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow) = 0;

      /**
       * @brief Terminate platform application
       */
      APP_API virtual void TerminateApplication() = 0;

      const std::shared_ptr<MApplicationEventHandler> GetEventHandler() const { return m_eventHandler; }
      const std::shared_ptr<MAbstractCursor> GetCursor() const { return m_cursor; }

    private:
      std::shared_ptr<MApplicationEventHandler> m_eventHandler;
      const std::shared_ptr<MAbstractCursor> m_cursor;
  };
} // namespace MEngine::Application

} // namespace MEngine

#endif // _ME_APP_ABSTRACT_APPLICATION_