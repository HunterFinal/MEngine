/**
 * モジュール : Delegate
 * 
 * デリゲートを生成するデフォルトファクトリー
 * 
 * 名前空間 : MEngine::Core
 */

#pragma once

#ifndef _ME_DELEGATE_FACTORY_
#define _ME_DELEGATE_FACTORY_

#include "Delegates/DelegateImpl.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    template<typename, typename>
    class MDelegate;

    /**
     * Default factory to create delegate
     */
    struct MDefaultDelegateFactory
    {
      /**
       * Create delegate with delegate instance that contains regular c/c++ function 
       * c/c++の普通関数が含まれるデリゲート生成
       */
      template<typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateStaticDelegateInstance(IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::FuncPtrType FuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>>(FuncPtr);

        return newDelegate;
      }

      /**
       * Create struct/class method delegate(non-const)
       * 非constメンバー関数が含まれるデリゲート生成
       */
      template<typename UserClass, typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateClassDelegateInstance(IN UserClass* InstancePtr, IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::template MemFuncPtrType<UserClass> MemFuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MClassMethodDelegateInstance<false, UserClass, ReturnType(ArgTypes...)>>(InstancePtr, MemFuncPtr);

        return newDelegate;
      }

      /**
       * Create struct/class method delegate(const)
       * Constメンバー関数が含まれるデリゲート生成
       */
      template<typename UserClass, typename ReturnType, typename... ArgTypes>
      FORCEINLINE static MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> CreateClassDelegateInstance(IN const UserClass* InstancePtr, IN typename MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory>::template ConstMemFuncPtrType<UserClass> ConstMemFuncPtr)
      {
        MDelegate<ReturnType(ArgTypes...), MDefaultDelegateFactory> newDelegate{};
        newDelegate.CreateDelegateInstance<MClassMethodDelegateInstance<true, const UserClass, ReturnType(ArgTypes...)>>(InstancePtr, ConstMemFuncPtr);

        return newDelegate;
      }

      /**
       * Not allowed to create an instance
       * インスタント生成禁止
       */
      MDefaultDelegateFactory() = delete;
      ~MDefaultDelegateFactory() = delete;
    };
  }
}

#endif // _ME_DELEGATE_FACTORY_