#pragma once

#ifndef _ME_WINDOWS_PLATFORM_LOW_LEVEL_ACCESS_PORT_
#define _ME_WINDOWS_PLATFORM_LOW_LEVEL_ACCESS_PORT_

#include "Generic/GenericPlatformLowLevelAccessPort.h"
#include "Macro/TypeAliasMacro.h"

namespace MEngine
{
  namespace Core
  {
    struct MWindowsPlatformLowLevelAccessPort : public MGenericPlatformLowLevelAccessPort
    {
      CORE_API static void PlatformPrintToLocalDevice(const TCHAR* Str);
    };
  }
}

TYPEDEF(MEngine::Core::MWindowsPlatformLowLevelAccessPort, MPlatformLowLevelAccessPort);

#endif // _ME_WINDOWS_PLATFORM_LOW_LEVEL_ACCESS_PORT_