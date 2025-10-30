/**
 * @file AbstractMulticastDelegate.h
 * @author MAI ZHICONG
 * @brief Base class of multicast delegate
 * @version 0.1
 * @date 2025-10-14
 * 
 * @copyright Copyright (c) 2025~2025 MAI ZHICONG
 * 
 */

#pragma once

#ifndef ME_ABSTRACT_MULTICAST_DELEGATE
#define ME_ABSTRACT_MULTICAST_DELEGATE

#include "Macro/CPPVerMacro.h"
#include "Misc/CoreDefines.h"
#include "Delegates/AbstractDelegate.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Delegates/IDelegateInterface.h"

#include <vector>
#include <memory>

namespace MEngine
{
  namespace Core
  {
    /**
     * Base of multicast delegate
     * Non thread-safe
     * Use it without multithreaded programming
     */
    class MAbstractMulticastDelegate
    {
      TYPEDEF(std::unique_ptr<MAbstractDelegate>, DelegateInst);
      TYPEDEF(std::vector<DelegateInst>, DelegateList);
      /**
       * Default constructor
       * Access only in derived class
       */
      protected:
        MAbstractMulticastDelegate() = default;

      /**
       * Destructor
       */
      public:
        CORE_API virtual ~MAbstractMulticastDelegate();

        /**
         * Move constructor
         */
        CORE_API MAbstractMulticastDelegate(IN MAbstractMulticastDelegate&& Other) noexcept;
        CORE_API MAbstractMulticastDelegate& operator=(IN MAbstractMulticastDelegate&& Other) noexcept;

        /**
         * Clear all delegate instance
         */
        CORE_API void ClearAll();
        
        /**
         * Remove delegate instance that binds to input handle
         * 
         * @param Handle Handle of delegate instance that user wants to remove
         * @return true if remove successfully, false otherwise
         */
        CORE_API bool Remove(IN const MDelegateHandle& Handle);

        /**
         * Remove delegate instance that use an input instance pointer
         * 
         * @param InstancePtr Pointer to instance
         * @return Return the number of delegate instances that successfully removed
         */
        CORE_API int32 RemoveAll(IN const void* InstancePtr);

        /**
         * Check if this multicast delegate is bound to any valid delegate instance
         * 
         * @return true if bound to a valid delegate instance, false otherwise
         */
        CORE_API bool IsBound() const;

        /**
         * Check if this multicast delegate has a delegate instance that bound to input instance pointer
         * 
         * @param InstancePtr Pointer of instance
         * @return True if any delegate instance bound to instance, false otherwise
         */
        CORE_API bool IsBoundToInstance(IN const void* InstancePtr) const;

      protected:

        /**
         * Add a new delegate instance to this multicast delegate
         * 
         * @template DelegateInstanceType Type of specific delegate instance
         * @param NewDelegateInstance New delegate instance
         * @return Handle of new-added delegate instance, return invalid handle if new delegate instance is invalid
         */
        template<typename DelegateType>
        FORCEINLINE MDelegateHandle AddDelegateInstance(DelegateType&& NewDelegateInstance);

        /**
         * Invoke all delegate instances added in this multicast delegate
         * 
         * @template DelegateInstanceInterfaceType Interface of delegate instance
         * @template... ArgTypes Argument types
         * @param Args Arguments to send to delegate instance
         */
        template<typename DelegateInstanceInterfaceType, typename... ArgTypes>
        FORCEINLINE void InvokeInternal(ArgTypes... Args) const;
    
    private:
      /**
       * Compact container of delegate
       */
      FORCEINLINE void CompactDelegateContainer();

      /**
       * Shrink the capacity of container
       */
      FORCEINLINE void ShrinkDelegateContainer();

      /**
       * Remove specific delegate from container
       * 
       * @param Delegate Delegate to remove
       * @return Remove count of delegate(may greater than 1 if have same delegates)
       */
      FORCEINLINE size_t EraseDelegate(const std::unique_ptr<MAbstractDelegate>& DelegatePtr);

      FORCEINLINE size_t GetDelegateNumInternal() const;

    private:
      DelegateList m_delegateList;  // Container to keep all singlecast delegate
    };

    template<typename DelegateType>
    MDelegateHandle MAbstractMulticastDelegate::AddDelegateInstance(DelegateType&& NewDelegate)
    {
      MDelegateHandle ResultHandle{};

      // Factory lambda
      auto deleInstFactory = [](DelegateType&& NewDelegate)
      {
        return std::make_unique<DelegateType>(std::forward<DelegateType>(NewDelegate));
      };

      if (NewDelegate.IsBound())
      {
        ResultHandle = NewDelegate.GetHandle();
        m_delegateList.emplace_back(deleInstFactory(std::forward<DelegateType>(NewDelegate)));
      }

      return ResultHandle;
    };

    template<typename DelegateInstanceInterfaceType, typename... ArgTypes>
    void MAbstractMulticastDelegate::InvokeInternal(ArgTypes... Args) const
    {
      bool bNeedCompact = false;
      for (const std::unique_ptr<MAbstractDelegate>& delegatePtr : m_delegateList)
      {
        const DelegateInstanceInterfaceType* delegateInstance = static_cast<const DelegateInstanceInterfaceType*>(delegatePtr->GetDelegateInterfaceInternal());
        if ((delegateInstance != nullptr) && delegateInstance->IsSafeToInvoke())
        {
          delegateInstance->Invoke(Args...);
        }
        else
        {
          bNeedCompact = true;
        }
      }

      if (bNeedCompact)
      {
        const_cast<MAbstractMulticastDelegate*>(this)->CompactDelegateContainer();
      }
    }

    void MAbstractMulticastDelegate::CompactDelegateContainer()
    {
      if (GetDelegateNumInternal() == 0ull)
      {
        return;
      }

      bool bNeedShrink = false;
      size_t listIndex = 0ull;

      while (listIndex < GetDelegateNumInternal())
      {
        std::unique_ptr<MAbstractDelegate>& delegatePtr = m_delegateList[listIndex];

        // TODO friend class breaks encapsulation
        IDelegateInterface* delegateInstance = delegatePtr->GetDelegateInterfaceInternal();
        if ((delegateInstance == nullptr) || !delegateInstance->IsSafeToInvoke())
        {
          EraseDelegate(delegatePtr);
          bNeedShrink = true;
          continue;
        }

        ++listIndex;
      }

      if (bNeedShrink)
      {
        ShrinkDelegateContainer();
      }
    }
    
    size_t MAbstractMulticastDelegate::EraseDelegate(const std::unique_ptr<MAbstractDelegate>& Delegate)
    {
      #if HAS_CPP_20
        return std::erase(m_delegateList, Delegate);
      #else
        auto removeItemIterator = std::remove(m_delegateList.begin(), m_delegateList.end(), Delegate);
        auto eraseRangeSize = std::distance(removeItemIterator, m_delegateList.end());
        m_delegateList.erase(removeItemIterator, m_delegateList.end());
        return (size_t)eraseRangeSize;
      #endif
    }

    size_t MAbstractMulticastDelegate::GetDelegateNumInternal() const
    {
      return m_delegateList.size();
    }

    void MAbstractMulticastDelegate::ShrinkDelegateContainer()
    {
      #if HAS_CPP_11
        m_delegateList.shrink_to_fit();
      #else
        std::vector<MAbstractDelegate> temp(m_delegateList).swap(m_delegateList);
      #endif
    }
  }
}

#endif // ME_ABSTRACT_MULTICAST_DELEGATE