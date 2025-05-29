// MDelegateHandle definition

#include "Delegates/IDelegateInterface.h"
#include <atomic>

namespace
{
  std::atomic<uint64> gNextDelegateHandleID{1};
}

const MDelegateHandle MDelegateHandle::NullHandle = MDelegateHandle{};

MDelegateHandle::MDelegateHandle(InitProtocol Protocol)
  : m_handleID(0)
{
  switch (Protocol)
  {
    case GenerateNew:
      m_handleID = GenerateNewID();
    default:
      break;
  }
}

bool MDelegateHandle::IsValid() const
{
  return *this != NullHandle;
}

void MDelegateHandle::Reset()
{
  m_handleID = 0;
}

bool operator==(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs)
{
  return Lhs.m_handleID == Rhs.m_handleID;
}

bool operator!=(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs)
{
  return Lhs.m_handleID != Rhs.m_handleID;
}

uint64 MDelegateHandle::GenerateNewID()
{
  /**Use self increment to generate ID */
  uint64 resultID = 0ull; // ull = unsigned long long

  resultID = ++gNextDelegateHandleID;
  
  if (resultID == 0ull)
  {
    resultID = ++gNextDelegateHandleID;
  }

  return resultID;
}
