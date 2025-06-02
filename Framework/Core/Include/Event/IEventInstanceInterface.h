﻿#pragma once

#ifndef _ME_IEVENT_INSTANCE_INTERFACE_
#define _ME_IEVENT_INSTANCE_INTERFACE_

#include "Event/IEventInterface.h"
#include "Misc/CoreDefines.h"

#include <cassert>
#include <type_traits>

namespace MEngine
{
  namespace Core
  {
    template<typename DerivedEventInstanceType>
    struct IEventInstanceInterface : public IEventInterface
    {

      CORE_API virtual ~IEventInstanceInterface() = default;
      
      template<typename... InvokeEventArgTypes>
      void InvokeEvent(InvokeEventArgTypes... Args)
      {
        static_cast<DerivedEventInstanceType*>(this)->Invoke(Args...);
      }
    };
  }
}

#endif // _ME_IEVENT_INSTANCE_INTERFACE_