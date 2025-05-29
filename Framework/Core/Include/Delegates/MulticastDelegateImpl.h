#pragma once

#ifndef ME_MULTICASE_DELEGATE_IMPL
#define ME_MULTICASE_DELEGATE_IMPL

#include "Delegates/AbstractMulticastDelegate.h"
#include "Delegates/FunctionPointerTypeTraits.h"
#include "Delegates/DelegateImpl.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Delegates/IDelegateInstanceInterface.h"
#include "Misc/CoreDefines.h"
#include "Macro/TypeAliasMacro.h"
#include "Templates/METemplates.h"

#include <cassert>
#include <type_traits>

namespace MEngine
{
  namespace Core
  {
    template<typename FuncType>
    class MMulticastDelegate;

    template<typename ReturnType, typename... ArgTypes>
    class MMulticastDelegate<ReturnType(ArgTypes...)>
    {
      static_assert(sizeof(ReturnType) == 0, "The return type of MMulticastDelegate must be void");
    };

    template<typename... ArgTypes>
    class MMulticastDelegate<void(ArgTypes...)> final : public MAbstractMulticastDelegate
    {
      private:
        TYPEDEF(void(ArgTypes...), FuncType);
        TYPEDEF(void (*)(ArgTypes...), FuncPtrType);
        TYPEDEF(MAbstractMulticastDelegate, Super);
        TYPEDEF(IDelegateInstanceInterface<FuncType>, IDelegateInstanceInterfaceType);
        TYPEDEF(MDelegate<void(ArgTypes...)>, SingleDelegate);

        // Avoid macro comma detection
        #define COMMA , 
        template<typename UserClass> TYPEDEF(typename ClassMemberFuncPtrType<false COMMA UserClass COMMA FuncType>::Type, MemFuncPtrType);
        template<typename UserClass> TYPEDEF(typename ClassMemberFuncPtrType<true COMMA const UserClass COMMA FuncType>::Type, ConstMemFuncPtrType);
        #undef COMMA

      public:
        explicit MMulticastDelegate() = default;
        ~MMulticastDelegate() = default;
        explicit MMulticastDelegate(TYPE_NULLPTR)
          : Super{}
        { }

        MMulticastDelegate(MMulticastDelegate&& Other) noexcept = default;
        MMulticastDelegate& operator=(MMulticastDelegate&& Other) noexcept = default;

        FORCEINLINE MDelegateHandle AddDelegate(SingleDelegate&& Delegate)
        {
          return Super::AddDelegateInstance(std::move(Delegate));
        }

        FORCEINLINE MDelegateHandle AddDelegate(const SingleDelegate& Delegate)
        {
          // TODO
          // need research:decay-copy
          // extra copy and destructor cause performance decrease
          return Super::AddDelegateInstance(CopyTemp(Delegate));
        }

        FORCEINLINE MDelegateHandle AddStatic(IN typename MStaticFunctionDelegateInstance<FuncType>::FuncPtrType FuncPtr)
        {
          SingleDelegate newDelegate{};
          newDelegate.BindStatic(FuncPtr);

          return Super::AddDelegateInstance(std::move(newDelegate));
        }

        template<typename UserClass>
        FORCEINLINE MDelegateHandle AddClass(IN UserClass* InstancePtr, IN MemFuncPtrType<UserClass> MemFuncPtr)
        {
          static_assert(!std::is_const_v<UserClass>, "Can't bind a delegate with const instance pointer and non-const member function.");
          
          SingleDelegate newDelegate{};
          newDelegate.BindClass(InstancePtr, MemFuncPtr);

          return Super::AddDelegateInstance(std::move(newDelegate));
        }

        template<typename UserClass>
        FORCEINLINE MDelegateHandle AddClass(IN const UserClass* InstancePtr, IN ConstMemFuncPtrType<UserClass> ConstMemFuncPtr)
        {
          SingleDelegate newDelegate{};
          newDelegate.BindClass(InstancePtr, ConstMemFuncPtr);

          return Super::AddDelegateInstance(std::move(newDelegate));
        }

        void Invoke(IN ArgTypes... Args) const
        {
          Super::InvokeInternal<IDelegateInstanceInterfaceType, ArgTypes...>(Args...);
        }

        void operator()(IN ArgTypes... Args) const
        {
          this->Invoke(Args...);
        }

        NODISCARD_MSG("Ignore delegate handle that added in multicast delegate") MDelegateHandle operator+=(IN const SingleDelegate& Delegate)
        {
          return this->AddDelegate(Delegate);
        }

        bool operator-=(IN const SingleDelegate& Delegate)
        {
          return Super::Remove(Delegate.GetHandle());
        }
    };
  }
}

#endif // ME_MULTICASE_DELEGATE_IMPL