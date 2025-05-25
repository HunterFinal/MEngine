#pragma once

#ifndef ME_DELEGATE_INSTANCE_IMPL
#define ME_DELEGATE_INSTANCE_IMPL

#include "Delegates/DelegateInstanceImplFwd.h"
#include "Delegates/FunctionPointerTypeTraits.h"
#include "Delegates/IDelegateInstanceInterface.h"
#include "Macro/TypeAliasMacro.h"

namespace MEngine
{
  namespace Core
  {
    /**Start of Delegate Instance Handle Holder */
    #pragma region Delegate Instance Handle Holder
    template<typename FuncType>
    class MDelegateInstanceHandleHolder : public IDelegateInstanceInterface<FuncType>
    {
      protected:
        explicit MDelegateInstanceHandleHolder();

      public:
        virtual ~MDelegateInstanceHandleHolder();
        /**Start of IDelegateInterface interface */
        FORCEINLINE MDelegateHandle GetHandle() const final;
        /**End of IDelegateInterface interface */

      private:
        MDelegateHandle m_handle;   // Handle of this delegate
    };

    template<typename FuncType>
    MDelegateInstanceHandleHolder<FuncType>::MDelegateInstanceHandleHolder()
      : m_handle(MDelegateHandle::InitProtocol::GenerateNew)
    { }

    template<typename FuncType>
    FORCEINLINE MDelegateHandle MDelegateInstanceHandleHolder<FuncType>::GetHandle() const
    {
      return m_handle;
    }

    template<typename FuncType>
    MDelegateInstanceHandleHolder<FuncType>::~MDelegateInstanceHandleHolder()
    {
      m_handle.Reset();
    }
    #pragma endregion Delegate Instance Handle Holder
    /**End of MDelegateInstanceHandleHolder */

    /**
     * Concentrate delegate instance
     */

    /**
     * regular c/c++ functions delegate instance
     */
    /**Start of regular C/C++ functions delegate instance */
    #pragma region Regular C/C++ functions delegate instance
    template<typename ReturnType, typename... ArgTypes>
    class MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)> final : public MDelegateInstanceHandleHolder<ReturnType(ArgTypes...)>
    {
      public:
        TYPEDEF(ReturnType(*)(ArgTypes...), FuncPtrType);
        TYPEDEF(MDelegateInstanceHandleHolder<ReturnType(ArgTypes...)>, Super);

        explicit MStaticFunctionDelegateInstance(IN FuncPtrType StaticFuncPtr);
        ~MStaticFunctionDelegateInstance();

        /**Start of IDelegateInterface interface */
        void* GetInstancePtr() const final;
        bool IsSafeToInvoke() const final;
        /**End of IDelegateInterface interface */

        /**Start of IDelegateInstanceInterface interface */
        ReturnType Invoke(IN ArgTypes... Args) const final;
        ReturnType operator()(IN ArgTypes... Args) const final;
        /**End of IDelegateInstanceInterface interface */

      private:
        FuncPtrType m_staticFuncPtr;
    };

    template<typename ReturnType, typename... ArgTypes>
    MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::MStaticFunctionDelegateInstance(IN FuncPtrType StaticFuncPtr)
      : Super{}
      , m_staticFuncPtr(StaticFuncPtr)
    {
      assert(m_staticFuncPtr != nullptr);
    }

    template<typename ReturnType, typename... ArgTypes>
    MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::~MStaticFunctionDelegateInstance()
    {
      m_staticFuncPtr = nullptr;
    }

    template<typename ReturnType, typename... ArgTypes>
    void* MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::GetInstancePtr() const
    {
      /**Regular c/c++ function don't need an instance */
      return nullptr;
    }

    template<typename ReturnType, typename... ArgTypes>
    bool MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::IsSafeToInvoke() const
    {
      /**Always safe to invoke */
      return true;
    }

    template<typename ReturnType, typename... ArgTypes>
    ReturnType MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::Invoke(IN ArgTypes... Args) const
    {
      assert(m_staticFuncPtr != nullptr);

      return m_staticFuncPtr(std::forward<ArgTypes>(Args)...);
    }

    template<typename ReturnType, typename... ArgTypes>
    ReturnType MStaticFunctionDelegateInstance<ReturnType(ArgTypes...)>::operator()(IN ArgTypes... Args) const
    {
      return this->Invoke(std::forward<ArgTypes>(Args)...);
    }
    #pragma endregion Regular C/C++ functions delegate
    /**End of regular C/C++ functions delegate instance */

    /**
     * struct/class member functions delegate instance
     */
    /**Start of struct/class member functions delegate instance */
    #pragma region Struct/Class member functions delegate
    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    class MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)> final : public MDelegateInstanceHandleHolder<ReturnType(ArgTypes...)>
    {
      public:
        // TYPEDEF((typename ClassMemberFuncPtrType<IsConst, UserClass, ReturnType(ArgTypes...)>::Type), MemberFuncType);
        using MemberFuncType = typename ClassMemberFuncPtrType<IsConst, UserClass, ReturnType(ArgTypes...)>::Type;
        TYPEDEF(MDelegateInstanceHandleHolder<ReturnType(ArgTypes...)>, Super);

        explicit MClassMethodDelegateInstance(IN UserClass* UserInstancePtr, IN MemberFuncType MemberFuncPtr);
        ~MClassMethodDelegateInstance();

        /**Start of IDelegateInterface interface */
        void* GetInstancePtr() const final;
        bool IsSafeToInvoke() const final;
        /**End of IDelegateInterface interface */

        /**Start of IDelegateInstanceInterface interface */
        ReturnType Invoke(IN ArgTypes... Args) const final;
        ReturnType operator()(IN ArgTypes... Args) const final;
        /**End of IDelegateInstanceInterface interface */

      private:
        UserClass* m_userInstancePtr;
        MemberFuncType m_memberFuncPtr;
    };

    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::MClassMethodDelegateInstance(IN UserClass* UserInstancePtr, IN MemberFuncType MemberFuncPtr)
      : Super{}
      , m_userInstancePtr(UserInstancePtr)
      , m_memberFuncPtr(MemberFuncPtr)
    {
      assert(m_userInstancePtr != nullptr);
      assert(m_memberFuncPtr != nullptr);
    }
    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::~MClassMethodDelegateInstance()
    {
      m_userInstancePtr = nullptr;
      m_memberFuncPtr = nullptr;
    }

    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    void* MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::GetInstancePtr() const
    {
      return static_cast<void*>(m_userInstancePtr);
    }

    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    bool MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::IsSafeToInvoke() const
    {
      // We never know whether or not it is safe to dereference a raw pointer,
      // so we try to trust the user
      return true;
    }

    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    ReturnType MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::Invoke(ArgTypes... Args) const
    {
      assert(m_userInstancePtr != nullptr);
      assert(m_memberFuncPtr != nullptr);

      return (m_userInstancePtr->*m_memberFuncPtr)(std::forward<ArgTypes>(Args)...);
    }

    template<bool IsConst, typename UserClass, typename ReturnType, typename... ArgTypes>
    ReturnType MClassMethodDelegateInstance<IsConst, UserClass, ReturnType(ArgTypes...)>::operator()(ArgTypes... Args) const
    {
      return this->Invoke(std::forward<ArgTypes>(Args)...);
    }
    #pragma endregion Regular C/C++ functions delegate instance
    /**End of struct/class member functions delegate instance */
  }
}

#endif // ME_DELEGATE_INSTANCE_IMPL

