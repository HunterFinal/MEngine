#include "Delegates/AbstractDelegate.h"

namespace MEngine
{
  namespace Core
  {
    MAbstractDelegate::~MAbstractDelegate()
    {
      Unbind();
    }

    void MAbstractDelegate::Unbind()
    {
      const IDelegateInterface* delegateInterface = GetDelegateInterfaceInternal();
      if (delegateInterface != nullptr)
      {
        delegateInterface->~IDelegateInterface();

        //TODO 
        // 16 is magic number for a delegate instance memory block minimal size
        m_allocator.Allocate(0, 16ull);
      }
    }

    bool MAbstractDelegate::IsBound() const
    {
      const IDelegateInterface* delegateInterface = GetDelegateInterfaceInternal();
      return (delegateInterface != nullptr) ? delegateInterface->IsSafeToInvoke() : false;
    }

    bool MAbstractDelegate::IsBoundToInstance(IN const void* InstancePtr) const
    {
      const IDelegateInterface* delegateInterface = GetDelegateInterfaceInternal();
      return (delegateInterface != nullptr) ? delegateInterface->IsBoundToInstance(InstancePtr) : false;
    }

    MDelegateHandle MAbstractDelegate::GetHandle() const
    {
      const IDelegateInterface* delegateInterface = GetDelegateInterfaceInternal();
      return (delegateInterface != nullptr) ? delegateInterface->GetHandle() : MDelegateHandle::NullHandle;
    }
        
    bool operator==(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs)
    {
      return Lhs.GetDelegateInterfaceInternal() == Rhs.GetDelegateInterfaceInternal();
    }

    bool operator!=(IN const MAbstractDelegate& Lhs, IN const MAbstractDelegate& Rhs)
    {
      return Lhs.GetDelegateInterfaceInternal() != Rhs.GetDelegateInterfaceInternal();
    }
  }
}