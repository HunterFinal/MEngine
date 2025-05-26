#include "Delegates/AbstractDelegate.h"

namespace MEngine
{
  namespace Core
  {
    MAbstractDelegate::~MAbstractDelegate()
    {
      Unbind();
    }

    MAbstractDelegate::MAbstractDelegate(IN MAbstractDelegate&& Other) noexcept
      : m_delegateInterface(std::move(Other.m_delegateInterface))
    { 
      Other.m_delegateInterface.reset();
    }
  
    MAbstractDelegate& MAbstractDelegate::operator=(IN MAbstractDelegate&& Other) noexcept
    {
      if (this != &Other)
      {
        std::unique_ptr<IDelegateInterface> temp = std::move(Other.m_delegateInterface);
        m_delegateInterface = std::move(temp);
        Other.m_delegateInterface.reset();
      }

      return *this;
    }

    void MAbstractDelegate::Unbind()
    {
      m_delegateInterface.reset();
    }

    void* MAbstractDelegate::GetInstancePtr() const
    {
      return (m_delegateInterface != nullptr) ? m_delegateInterface->GetInstancePtr() : nullptr;
    }

    bool MAbstractDelegate::IsBound() const
    {
      return (m_delegateInterface != nullptr) ? m_delegateInterface->IsSafeToInvoke() : false;
    }

    bool MAbstractDelegate::IsBoundToInstance(IN const void* InstancePtr) const
    {
      return (m_delegateInterface != nullptr) ? m_delegateInterface->IsBoundToInstance(InstancePtr) : false;
    }

    MDelegateHandle MAbstractDelegate::GetHandle() const
    {
      return (m_delegateInterface != nullptr) ? m_delegateInterface->GetHandle() : MDelegateHandle::NullHandle;
    }

  }
}