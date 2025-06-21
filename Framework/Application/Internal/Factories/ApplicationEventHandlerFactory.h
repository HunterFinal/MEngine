#pragma once

#ifndef _ME_APPLICATION_EVENT_HANDLER_FACTORY_
#define _ME_APPLICATION_EVENT_HANDLER_FACTORY_

#include "Macro/ApplicationDefines.h"
#include "APP_Generic/ApplicationEventHandlerFwd.h"

namespace std
{
  // TODO shared_ptr forward declaration
  template<typename _Ty> class shared_ptr;
}

namespace MEngine
{
  namespace Application
  {
    struct MApplicationEventHandlerFactory
    {
      APP_API static std::shared_ptr<MNullApplicationEventHandler> CreateNullEventHandler();

      MApplicationEventHandlerFactory() = delete;
      ~MApplicationEventHandlerFactory() = delete;
    };
  }
}

#endif // _ME_APPLICATION_EVENT_HANDLER_FACTORY_