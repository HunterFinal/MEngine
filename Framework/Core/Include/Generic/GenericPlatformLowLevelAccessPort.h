#pragma once

#ifndef _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_
#define _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_

#include "CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    struct MGenericPlatformLowLevelAccessPort
    {
      CORE_API static bool IsDebuggerPresent();
      CORE_API static void PlatformPrintDebugString(const TCHAR* Str);
      CORE_API static void PlatformPrintToLocalDevice(const TCHAR* Str);
    };
  }
}

#endif // _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_