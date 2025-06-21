#include "Generic/GenericPlatformLowLevelAccessPort.h"

#include "HAL/PlatformLowLevelAccessPort.h"

// TODO maybe use printf later
#include <cstdio>
#include <iostream>

namespace MEngine
{
  namespace Core
  {
    bool MGenericPlatformLowLevelAccessPort::IsDebuggerPresent()
    {
      #if ME_DEBUG_ON
        return true;
      #else
        return false;
      #endif
    }

    void MGenericPlatformLowLevelAccessPort::PlatformPrintDebugString(const TCHAR* Str)
    {
      MPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(Str);
    }

    void MGenericPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(const TCHAR* Str)
    {
      #if ((defined(UNICODE) && UNICODE) || (defined(_UNICODE) && _UNICODE))
        std::wcout << Str;
      #else
        std::cout << Str;
      #endif
    }
  }
}