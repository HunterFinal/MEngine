#pragma once

#ifndef _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_
#define _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    struct MGenericPlatformLowLevelAccessPort
    {
      CORE_API static bool IsDebuggerPresent();
      CORE_API static void OutputDebugString(const TCHAR* Str);
      CORE_API static void OutputToLocalDevice(const TCHAR* Str);
    };
  }
}

#endif // _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_