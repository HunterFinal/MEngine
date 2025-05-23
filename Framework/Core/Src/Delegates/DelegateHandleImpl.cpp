#include "IDelegateInterface.h"

namespace MEngine
{
  namespace Core
  {
    MDelegateHandle::MDelegateHandle()
      : m_handleID(0)
    { }

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
  }
}