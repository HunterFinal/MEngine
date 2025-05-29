#pragma once

#ifndef ME_DELEGATE_IMPL
#define ME_DELEGATE_IMPL

#include "Delegates/AbstractDelegate.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Delegates/FunctionPointerTypeTraits.h"
#include "Delegates/IDelegateInstanceInterface.h"
#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"
#include "Misc/CoreDefines.h"

#include <cassert>
#include <type_traits>

namespace MEngine
{
  namespace Core
  {
    template<typename FuncType>
    class MDelegate;
    
    template<typename ReturnType, typename... ArgTypes>
    class MDelegate<ReturnType(ArgTypes...)> : public MAbstractDelegate
    {
      public:
        TYPEDEF(ReturnType(ArgTypes...), FuncType);
        TYPEDEF(MAbstractDelegate, Super);
        TYPEDEF(IDelegateInstanceInterface<FuncType>, IDelegateInstanceInterfaceType);
        
        // Avoid macro comma detection
        #define COMMA , 
        template<typename UserClass> TYPEDEF(typename ClassMemberFuncPtrType<false COMMA UserClass COMMA FuncType>::Type, MemFuncType);
        template<typename UserClass> TYPEDEF(typename ClassMemberFuncPtrType<true COMMA const UserClass COMMA FuncType>::Type, ConstMemFuncType);
        #undef COMMA

      public:
        explicit MDelegate() = default;
        ~MDelegate() = default;
        FORCEINLINE explicit MDelegate(TYPE_NULLPTR)
        { }
    
        MDelegate(MDelegate&& Other) noexcept = default;
        MDelegate& operator=(MDelegate&& Other) noexcept = default;

        FORCEINLINE MDelegate(const MDelegate& Other)
        {
          CopyImpl(Other);
        }
        FORCEINLINE MDelegate& operator=(const MDelegate& Other)
        {
          CopyImpl(Other);
          return *this;
        }
        /**
         * Bind function to delegate
         */
        
        /**Start of MDelegate bind function group*/
        #pragma region MDelegate bind function group
    
        // Regular c/c++ function
        FORCEINLINE void BindStatic(IN typename MStaticFunctionDelegateInstance<FuncType>::FuncPtrType FuncPtr)
        {
          Super::CreateDelegateInstance<MStaticFunctionDelegateInstance<FuncType>>(FuncPtr);
        }

        // Struct/Class member function
        // non-const version
        template<typename UserClass>
        FORCEINLINE void BindClass(IN UserClass* InstancePtr, IN MemFuncType<UserClass> MemFuncPtr)
        {
          static_assert(!std::is_const_v<UserClass>, "Can't bind a delegate with const instance pointer and non-const member function.");
          Super::CreateDelegateInstance<MClassMethodDelegateInstance<false, UserClass, FuncType>>(InstancePtr,MemFuncPtr);
        }
        // const version
        template<typename UserClass>
        FORCEINLINE void BindClass(IN const UserClass* InstancePtr, IN ConstMemFuncType<UserClass> ConstMemFuncPtr)
        {
          Super::CreateDelegateInstance<MClassMethodDelegateInstance<true, const UserClass, FuncType>>(InstancePtr, ConstMemFuncPtr);
        }
    
        #pragma endregion MDelegate bind function group
        /**End of MDelegate bind function group*/
        
        FORCEINLINE ReturnType Invoke(ArgTypes... Args) const
        {
          const IDelegateInstanceInterfaceType* delegateInstance = GetDelegateInterfaceInternal();
          assert(delegateInstance != nullptr);

          return delegateInstance->Invoke(std::forward<ArgTypes>(Args)...);
        }

        FORCEINLINE ReturnType operator()(ArgTypes... Args) const
        {
          return this->Invoke(std::forward<ArgTypes>(Args)...);
        }

      private:
        FORCEINLINE IDelegateInstanceInterfaceType* GetDelegateInterfaceInternal()
        {
          return static_cast<IDelegateInstanceInterfaceType*>(Super::GetDelegateInterfaceInternal());
        }

        FORCEINLINE const IDelegateInstanceInterfaceType* GetDelegateInterfaceInternal() const
        {
          return static_cast<const IDelegateInstanceInterfaceType*>(Super::GetDelegateInterfaceInternal());
        }

      private:
        void CopyImpl(const MDelegate& Other)
        {
          if (this == &Other)
          {
            return;
          }

          MDelegate temp{};

          {
            const IDelegateInstanceInterface<ReturnType(ArgTypes...)>* delegateInterface = Other.GetDelegateInterfaceInternal();
            if (delegateInterface != nullptr)
            {
              delegateInterface->CreateCopy(temp);
            }
          }

          *this = std::move(temp);
        }
    };
  }
}

#endif // ME_DELEGATE_IMPL