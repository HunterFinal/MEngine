#include "Utils/RHICommandIterator.h"
#include "RHICommand.h"

namespace MEngine
{

namespace RHI
{

MRHICommandIterator& MRHICommandIterator::operator++()
{
  if (m_ptr != nullptr)
  {
    m_ptr = m_ptr->Next;
  }

  return *this;
}

MRHICommandIterator MRHICommandIterator::operator++(int32)
{
  MRHICommandIterator Prev{*this};
  if (m_ptr != nullptr)
  {
    m_ptr = m_ptr->Next;
  }

  return Prev;
}

IRHICommand& MRHICommandIterator::operator*()
{
  return *m_ptr;
}
  
bool operator==(const MEngine::RHI::MRHICommandIterator& Lhs, const MEngine::RHI::MRHICommandIterator& Rhs)
{
  return Lhs.m_ptr == Rhs.m_ptr;
}

bool operator!=(const MEngine::RHI::MRHICommandIterator& Lhs, const MEngine::RHI::MRHICommandIterator& Rhs)
{
  return !(Lhs == Rhs);
}

}

}
