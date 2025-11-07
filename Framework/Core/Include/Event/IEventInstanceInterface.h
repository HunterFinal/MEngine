#pragma once

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
      static_assert(std::is_base_of_v<IEventInstanceInterface, DerivedEventInstanceType>, "Derived class is not an IEventInstanceInterface");
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