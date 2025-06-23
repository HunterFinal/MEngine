#pragma once

#ifndef _ME_APP_NULL_APPLICATION_EVENT_HANDLER_
#define _ME_APP_NULL_APPLICATION_EVENT_HANDLER_

#include "APP_Generic/ApplicationEventHandler.h"

namespace MEngine
{
  namespace Application
  {
    struct MNullApplicationEventHandler final : public MApplicationEventHandler
    {
      public:
        APP_API ~MNullApplicationEventHandler();

        /**Start of MApplicationEventHandler interface */
        #pragma region MApplicationEventHandler interface

        APP_API bool OnKeyDown(IN const MKeyInputInfoContainer& Container) override final;
        APP_API bool OnKeyUp(IN const MKeyInputInfoContainer& Container) override final;
        APP_API bool OnKeyChar(IN const MKeyCharContainer& Container) override final;
        APP_API bool OnMouseDown() override final;
        APP_API bool OnMouseUp() override final;
        APP_API bool OnMouseMove() override final;
        APP_API void OnWindowCreate(IN const std::shared_ptr<MAbstractApplicationWindow>& Window, IN const bool bIsSetFocus) override final;
        APP_API void OnWindowClose(IN const std::shared_ptr<MAbstractApplicationWindow>& Window) override;
        
        #pragma endregion MApplicationEventHandler interface
        /**End of MApplicationEventHandler interface */
    };
  }
}

#endif // _ME_APP_NULL_APPLICATION_EVENT_HANDLER_