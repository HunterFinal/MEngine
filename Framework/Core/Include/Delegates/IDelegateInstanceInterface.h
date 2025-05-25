#pragma once

#ifndef ME_DELEGATE_INSTANCE_INTERFACE
#define ME_DELEGATE_INSTANCE_INTERFACE

#include "Delegates/IDelegateInterface.h"
#include "Delegates/FunctionPointerTypeTraits.h"

namespace MEngine
{
  namespace Core
  {
    template<typename FuncType>
    struct IDelegateInstanceInterface;

    template<typename ReturnType, typename... ArgTypes>
    struct IDelegateInstanceInterface<ReturnType(ArgTypes...)> : public IDelegateInterface
    {
      /**
       * Invoke this delegate. Error occurs if the function pointer or instance(used by function pointer) is not valid.
       */
      virtual ReturnType Invoke(IN ArgTypes... Args) const = 0;

      /**
       * Invoke this delegate by operator(). Error occurs if the function pointer or instance(used by function pointer) is not valid.
       */
      virtual ReturnType operator()(IN ArgTypes... Args) const = 0;
    };
  }
}


#endif // ME_DELEGATE_INSTANCE_INTERFACE