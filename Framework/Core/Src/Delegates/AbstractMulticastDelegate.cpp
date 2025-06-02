#include "Delegates/AbstractMulticastDelegate.h"

namespace MEngine
{
  namespace Core
  {
    MAbstractMulticastDelegate::~MAbstractMulticastDelegate()
    {
      ClearAll();
    }

    MAbstractMulticastDelegate::MAbstractMulticastDelegate(IN MAbstractMulticastDelegate&& Other) noexcept
      : m_delegateList(std::move(Other.m_delegateList))
    { }

    MAbstractMulticastDelegate& MAbstractMulticastDelegate::operator=(IN MAbstractMulticastDelegate&& Other) noexcept
    {
      if (this != &Other)
      {
        m_delegateList.clear();
        m_delegateList = std::move(Other.m_delegateList);
        Other.m_delegateList.clear();
      }

      return *this;
    }

    void MAbstractMulticastDelegate::ClearAll()
    {
      for (std::unique_ptr<MAbstractDelegate>& delegatePtr : m_delegateList)
      {
        delegatePtr->Unbind();
      }

      CompactDelegateContainer();
    }

    bool MAbstractMulticastDelegate::Remove(IN const MDelegateHandle& Handle)
    {
      if (!Handle.IsValid())
      {
        return false;
      }
      
      for (size_t index = 0ull; index < m_delegateList.size(); ++index)
      {
        std::unique_ptr<MAbstractDelegate>& delegatePtr = m_delegateList[index];

        if (delegatePtr->GetHandle() == Handle)
        {
          delegatePtr->Unbind();
          CompactDelegateContainer();
          return true;
        }
      }

      return false;
    }

    int32 MAbstractMulticastDelegate::RemoveAll(IN const void* InstancePtr)
    {
      int32 removeCnt = 0;
      for (std::unique_ptr<MAbstractDelegate>& delegatePtr : m_delegateList)
      {
        const IDelegateInterface* delegateInterface = delegatePtr->GetDelegateInterfaceInternal();
        if ((delegateInterface != nullptr) && delegateInterface->IsBoundToInstance(InstancePtr))
        {
          delegatePtr->Unbind();
          ++removeCnt;
        }
      }

      if (removeCnt > 0)
      {
        CompactDelegateContainer();
      }

      return removeCnt;
    }

    bool MAbstractMulticastDelegate::IsBound() const
    {
      for (const std::unique_ptr<MAbstractDelegate>& delegatePtr : m_delegateList)
      {
        // TODO friend class breaks encapsulation
        const IDelegateInterface* delegateInterface = delegatePtr->GetDelegateInterfaceInternal();
        if ((delegateInterface != nullptr) && delegateInterface->IsSafeToInvoke())
        {
          return true;
        }
      }

      return false;
    }

    bool MAbstractMulticastDelegate::IsBoundToInstance(IN const void* InstancePtr) const
    {
      // TODO friend class breaks encapsulation
      for (const std::unique_ptr<MAbstractDelegate>& delegatePtr : m_delegateList)
      {
        const IDelegateInterface* delegateInterface = delegatePtr->GetDelegateInterfaceInternal();
        if ((delegateInterface != nullptr) && delegateInterface->IsBoundToInstance(InstancePtr))
        {
          return true;
        }
      }

      return false;
    }
  }
}