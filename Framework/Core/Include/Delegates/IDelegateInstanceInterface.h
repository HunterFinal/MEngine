#pragma once

#ifndef ME_DELEGATE_INSTANCE_INTERFACE
#define ME_DELEGATE_INSTANCE_INTERFACE

#include "Delegates/IDelegateInterface.h"
#include "Delegates/FunctionPointerTypeTraits.h"

namespace MEngine
{
  namespace Core
  {
    /**
     * Forward declaration
     */
    template<typename FuncType>
    struct IDelegateInstanceInterface;

    class MAbstractDelegate;

    template<typename ReturnType, typename... ArgTypes>
    struct IDelegateInstanceInterface<ReturnType(ArgTypes...)> : public IDelegateInterface
    {
      /**
       * Create delegate instance copy for MAbstractDelegate
       * 
       * @param DelegateCopy Target delegate to put copied delegate instance
       */
      virtual void CreateCopy(OUT MAbstractDelegate& DelegateCopy) const = 0;

      /**
       * Invoke this delegate. Error occurs if the function pointer or instance(used by function pointer) is not valid.
       * 
       * @param Args Input arguments to invoke delegate
       * @return Return result, Don't return if ReturnType is void
       */
      virtual ReturnType Invoke(IN ArgTypes... Args) const = 0;

      /**
       * Invoke this delegate by operator(). Error occurs if the function pointer or instance(used by function pointer) is not valid.
       * 
       * @param Args Input arguments to invoke delegate
       * @return Return result, Don't return if ReturnType is void
       */
      virtual ReturnType operator()(IN ArgTypes... Args) const = 0;
    };
  }
}


#endif // ME_DELEGATE_INSTANCE_INTERFACE