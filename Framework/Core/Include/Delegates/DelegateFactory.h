#pragma once

#ifndef ME_DELEGATE_FACTORY
#define ME_DELEGATE_FACTORY

#include "Delegates/DelegateImpl.h"
#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    struct MDefaultDelegateFactory
    {
      template<typename ReturnType, typename... ArgTypes>
      NODISCARD_MSG("Ignore delegate created by factory") FORCEINLINE static MDelegate<ReturnType(ArgTypes...)> CreateStatic(IN typename MDelegate<ReturnType(ArgTypes...)>::FuncType FuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...)> newDelegate{};
        newDelegate.CreateDelegateInstance<MStaticFunctionDelegateInstance>(FuncPtr);

        return newDelegate;
      }
      private:
        MDefaultDelegateFactory();
        ~MDefaultDelegateFactory();
    };
  }
}

#endif // ME_DELEGATE_FACTORY