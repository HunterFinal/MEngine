#pragma once

#ifndef ME_ABSTRACT_DELEGATE
#define ME_ABSTRACT_DELEGATE

#include "Math/MEngineMathUtility.h"
#include "Misc/CoreDefines.h"
#include "Allocation/Allocator.h"
#include "Delegates/IDelegateInterface.h"

#include <memory>

namespace MEngine
{
  namespace Core
  {
    /**
     * Base of singlecast delegate
     * Non thread-safe
     * Use it without multithreaded programming
     */
    class MAbstractDelegate
    {
      /**
       * friend class
       */
      #pragma region Friend class
      template<typename>
      friend class MStaticFunctionDelegateInstance;

      template<bool, typename, typename>
      friend class MClassMethodDelegateInstance;

      friend class MAbstractMulticastDelegate;
      #pragma endregion Friend class
      
      /**
       * Default constructor
       * Access only in derived class
       */
      protected:
        explicit MAbstractDelegate() = default;

      /**
       * Destructor
       */
      public:
        CORE_API virtual ~MAbstractDelegate();

        /**
         * Move constructor
         */
        MAbstractDelegate(IN MAbstractDelegate&& Other) noexcept = default;
        MAbstractDelegate& operator=(IN MAbstractDelegate&& Other) noexcept = default;

        /**
         * Equality compare operator
         */
        CORE_API friend bool operator==(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs);
        CORE_API friend bool operator!=(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs);
        
        /**
         * Unbind delegate instance
         */
        CORE_API void Unbind();

        /**
         * Get instance ptr used by delegate instance as specific <UserClass> type
         * 
         * @template UserClass User-defined class type
         * @return User instance ptr as specific type, return nullptr if it's not inherited to <UserClass>
         */
        template<typename UserClass>
        FORCEINLINE UserClass* GetTypedInstancePtr() const;

        /**
         * Check if this delegate is bound to a valid delegate instance
         * 
         * @return true if bound to a valid delegate instance, false otherwise
         */
        CORE_API bool IsBound() const;

        /**
         * Check if this delegate has a user instance ptr
         * 
         * @param InstancePtr User instance ptr
         * @return true if has a valid delegata instance and using a user instance ptr, false otherwise
         */
        CORE_API bool IsBoundToInstance(IN const void* InstancePtr) const;

        /**
         * Get handle that is keeping by delegate instance
         * 
         * @return handle of delegate instance if delegate instance is valid, invalid handle otherwise
         */
        CORE_API MDelegateHandle GetHandle() const;
        
      protected:
        /**
         * Create a delegate instance
         * Access only in a derived class
         * 
         * @template DelegateInstanceType Delegate instance that wants to create
         * @template... InstanceConstrucParamTypes Parameter types to construct delegate instance
         * @param Params Parameters use to construct delegate instance
         */
        template<typename DelegateType, typename... InstanceConstrucParamTypes>
        FORCEINLINE void CreateDelegateInstance(IN InstanceConstrucParamTypes... Params);
        
        /**
         * Get delegate instance interface
         * Access only in a derived class
         * 
         * @return Delegate instance interface, return nullptr if is not allocated
         */
        FORCEINLINE IDelegateInterface* GetDelegateInterfaceInternal();
        FORCEINLINE const IDelegateInterface* GetDelegateInterfaceInternal() const;

      private:
        /**
         * Allocate memory for delegate instance
         * 
         * @param AllocSize Size(byte) of memory allocation
         * @return Pointer of allocated delegate instance
         */
        void* AllocateInternal(IN SIZE_T AllocSize)
        {
          // TODO
          // 16 is a magic number of block size of each delegate instance;
          const SIZE_T delegateInstanceElementNum = MMath::DivideCeil(AllocSize, static_cast<SIZE_T>(16));
          m_allocator.Allocate(delegateInstanceElementNum, static_cast<SIZE_T>(16));

          return reinterpret_cast<void*>(m_allocator.GetAllocation());
        }

      private:
        DefaultAllocator<IDelegateInterface> m_allocator; // Allocator that manage memory of delegate instance

      public:
        /**
         * Uncopyable
         */
        MAbstractDelegate(const MAbstractDelegate&) = delete;
        MAbstractDelegate& operator=(const MAbstractDelegate&) = delete;
    };

    template<typename UserClass>
    UserClass* MAbstractDelegate::GetTypedInstancePtr() const
    {
      return dynamic_cast<UserClass*>(m_allocator.GetAllocation());
    }

    template<typename DelegateType, typename... InstanceConstrucParamTypes>
    void MAbstractDelegate::CreateDelegateInstance(IN InstanceConstrucParamTypes... Params)
    {
      const IDelegateInterface* delegateInterface = m_allocator.GetAllocation();

      // placement new must call destructor manually
      if(delegateInterface != nullptr)
      {
        delegateInterface->~IDelegateInterface();
      }

      new(AllocateInternal(sizeof(DelegateType))) DelegateType(std::forward<InstanceConstrucParamTypes>(Params)...);
    }

    IDelegateInterface* MAbstractDelegate::GetDelegateInterfaceInternal()
    {
      return const_cast<IDelegateInterface*>(static_cast<const MAbstractDelegate*>(this)->GetDelegateInterfaceInternal());
    }

    const IDelegateInterface* MAbstractDelegate::GetDelegateInterfaceInternal() const
    {
      return m_allocator.GetAllocation();
    }
  }
}

#endif // ME_ABSTRACT_DELEGATE