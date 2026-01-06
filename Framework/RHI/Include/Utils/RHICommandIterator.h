#pragma once

#ifndef _ME_RHI_COMMANDITERATOR_
#define _ME_RHI_COMMANDITERATOR_

#include "CoreDefines.h"

namespace MEngine
{

namespace RHI
{

class IRHICommand;

class MRHICommandIterator
{

public:
  explicit MRHICommandIterator(IN IRHICommand* Ptr)
    : m_ptr{Ptr}
  { }

  MRHICommandIterator& operator++();
  MRHICommandIterator  operator++(int32);
  IRHICommand&         operator*();

  
  friend bool operator==(const MRHICommandIterator& Lhs, const MRHICommandIterator& Rhs);
  friend bool operator!=(const MRHICommandIterator& Lhs, const MRHICommandIterator& Rhs);

private:
  mutable IRHICommand* m_ptr;
};

} // namespace MEngine::RHI

} // namespace MEngine




#endif // _ME_RHI_COMMANDITERATOR_