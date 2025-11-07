

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

  class MModifierKeysState
  {
    public:
      constexpr explicit MModifierKeysState(
        IN const bool bInIsLeftShiftPressed,
        IN const bool bInIsRightShiftPressed,
        IN const bool bInIsLeftControlPressed,
        IN const bool bInIsRightControlPressed,
        IN const bool bInIsLeftAltPressed,
        IN const bool bInIsRightAltPressed,
        IN const bool bInIsLeftCommandPressed,
        IN const bool bInIsRightCommandPressed
      )
        : bIsLeftShiftPressed{bInIsLeftShiftPressed}
        , bIsRightShiftPressed{bInIsRightShiftPressed}
        , bIsLeftControlPressed{bInIsLeftControlPressed}
        , bIsRightControlPressed{bInIsRightControlPressed}
        , bIsLeftAltPressed{bInIsLeftAltPressed}
        , bIsRightAltPressed{bInIsRightAltPressed}
        , bIsLeftCommandPressed{bInIsLeftCommandPressed}
        , bIsRightCommandPressed{bInIsRightCommandPressed}
      { }

      constexpr explicit MModifierKeysState()
        : bIsLeftShiftPressed{false}
        , bIsRightShiftPressed{false}
        , bIsLeftControlPressed{false}
        , bIsRightControlPressed{false}
        , bIsLeftAltPressed{false}
        , bIsRightAltPressed{false}
        , bIsLeftCommandPressed{false}
        , bIsRightCommandPressed{false}
      { }

    public:
      bool IsLeftShiftPressed() const
      {
        return bIsLeftShiftPressed;
      }

      bool IsRightShiftPressed() const
      {
        return bIsRightShiftPressed;
      }

      bool IsShiftPressed() const
      {
        return IsLeftShiftPressed() || IsRightShiftPressed();
      }

      bool IsLeftControlPressed() const
      {
        return bIsLeftControlPressed;
      }

      bool IsRightControlPressed() const
      {
        return bIsRightControlPressed;
      }

      bool IsControlPressed() const
      {
        return IsLeftControlPressed() || IsRightControlPressed();
      }

      bool IsLeftAltPressed() const
      {
        return bIsLeftAltPressed;
      }

      bool IsRightAltPressed() const
      {
        return bIsRightAltPressed;
      }

      bool IsAltPressed() const
      {
        return IsLeftAltPressed() || IsRightAltPressed();
      }

      bool IsLeftCommandPressed() const
      {
        return bIsLeftCommandPressed;
      }

      bool IsRightCommandPressed() const
      {
        return bIsRightCommandPressed;
      }

      bool IsCommandPressed() const
      {
        return IsLeftCommandPressed() || IsRightCommandPressed();
      }

    private:
      uint8 bIsLeftShiftPressed : 1;
      uint8 bIsRightShiftPressed : 1;
      uint8 bIsLeftControlPressed : 1;
      uint8 bIsRightControlPressed : 1;
      uint8 bIsLeftAltPressed : 1;
      uint8 bIsRightAltPressed : 1;
      uint8 bIsLeftCommandPressed : 1;
      uint8 bIsRightCommandPressed : 1;
  };
  
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

      virtual MModifierKeysState GetModState() const { return MModifierKeysState{};}

      const std::shared_ptr<MApplicationEventHandler> GetEventHandler() const { return m_eventHandler; }
      const std::shared_ptr<MAbstractCursor> GetCursor() const { return m_cursor; }

    private:
      std::shared_ptr<MApplicationEventHandler> m_eventHandler;
      const std::shared_ptr<MAbstractCursor> m_cursor;
  };
} // namespace MEngine::Application

} // namespace MEngine

#endif // _ME_APP_ABSTRACT_APPLICATION_