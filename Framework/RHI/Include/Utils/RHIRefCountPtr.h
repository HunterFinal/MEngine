#pragma once

#ifndef _ME_RHI_REFCOUNTPTR_
#define _ME_RHI_REFCOUNTPTR_

#include "RHIDefines.h"
#include "RHIConcepts.h"
#include "Macro/AssertionMacros.h"

namespace MEngine
{

namespace RHI
{

class MRHIResource;

template<typename RefType>
Requires_Derived_From(RefType, MEngine::RHI::MRHIResource)
class TRHIRefCountPtr
{
  TYPEDEF(RefType*, RefPtr);

public:
  TRHIRefCountPtr()
    : m_ref{nullptr}
  { }

  TRHIRefCountPtr(IN RefType* Ref)
    : m_ref{Ref}
  {
    if (m_ref != nullptr)
    {
      m_ref->AddRef();
    }
  }

  TRHIRefCountPtr(const TRHIRefCountPtr& OtherCopy)
    : m_ref{OtherCopy.m_ref}
  {
    if (m_ref != nullptr)
    {
      m_ref->AddRef();
    }
  }

  TRHIRefCountPtr(TRHIRefCountPtr&& OtherMove)
    : m_ref{OtherMove.m_ref}
  {
    OtherMove.m_ref = nullptr;
  }

  ~TRHIRefCountPtr()
  {
    if (m_ref != nullptr)
    {
      m_ref->RemoveRef();
    }
  }

  TRHIRefCountPtr& operator=(const TRHIRefCountPtr& OtherCopy)
  {
    if (m_ref != OtherCopy.m_ref)
    {
      if (OtherCopy.m_ref != nullptr)
      {
        OtherCopy.m_ref->AddRef();
      }
      if (m_ref != nullptr)
      {
        m_ref->RemoveRef();
      }

      m_ref = OtherCopy.m_ref;
    }

    return *this;
  }

  TRHIRefCountPtr& operator=(TRHIRefCountPtr&& OtherMove)
  {
    if (this != &OtherMove)
    {
      if (this->m_ref != nullptr)
      {
        this->m_ref->RemoveRef();
      }

      this->m_ref = OtherMove.m_ref;
      OtherMove.m_ref = nullptr;
    }

    return *this;
  }
  
  RefPtr operator->() const
  {
    return m_ref;
  }

  operator RefPtr() const
  {
    return m_ref;
  }

  RefPtr Get() const
  {
    return m_ref;
  }

  bool IsValid() const
  {
    return m_ref != nullptr;
  }

  uint32 GetRefCount() const
  {
    if (IsValid())
    {
      uint32 result = m_ref->GetRefCount();
      me_assert(result > 0);

      return result;
    }

    return 0;
  }

private:
  RefPtr m_ref;
};

}

}


#endif // _ME_RHI_REFCOUNTPTR_