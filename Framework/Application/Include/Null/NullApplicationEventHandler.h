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
        ~MNullApplicationEventHandler();

        /**Start of MApplicationEventHandler interface */
        #pragma region MApplicationEventHandler interface

        bool OnKeyDown() override final;
        bool OnKeyUp() override final;
        bool OnMouseDown() override final;
        bool OnMouseUp() override final;
        bool OnMouseMove() override final;
        
        #pragma endregion MApplicationEventHandler interface
        /**End of MApplicationEventHandler interface */
    };
  }
}

#endif // _ME_APP_NULL_APPLICATION_EVENT_HANDLER_