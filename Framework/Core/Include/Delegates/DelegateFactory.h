#pragma once

#ifndef ME_DELEGATE_FACTORY
#define ME_DELEGATE_FACTORY

#include "Delegates/DelegateImpl.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    /**
     * Forward declaration
     */
    template<typename, typename>
    class MDelegate;

    struct MDefaultDelegateFactory
    {
      template<typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateStaticDelegateInstance(IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::FuncPtrType FuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>>(FuncPtr);

        return newDelegate;
      }

      template<typename UserClass, typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateClassDelegateInstance(IN UserClass* InstancePtr, IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::template MemFuncPtrType<UserClass> MemFuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MClassMethodDelegateInstance<false, UserClass, ReturnType(ArgTypes...)>>(InstancePtr, MemFuncPtr);

        return newDelegate;
      }

      template<typename UserClass, typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateClass(IN const UserClass* InstancePtr, IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::template ConstMemFuncPtrType<UserClass> ConstMemFuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MClassMethodDelegateInstance<true, const UserClass, ReturnType(ArgTypes...)>>(InstancePtr, ConstMemFuncPtr);

        return newDelegate;
      }

      MDefaultDelegateFactory() = delete;
      ~MDefaultDelegateFactory() = delete;
    };
  }
}

#endif // ME_DELEGATE_FACTORY