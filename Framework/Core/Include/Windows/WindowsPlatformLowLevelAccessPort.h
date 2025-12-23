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
      static CORE_API void PlatformPrintToLocalDevice(const TCHAR* Str);

      static CORE_API void* GetDLLLibrary(IN const TCHAR* FileName);
      static CORE_API void UnloadDLLLibrary(IN const void* Handle);
    };
  }
}

TYPEDEF(MEngine::Core::MWindowsPlatformLowLevelAccessPort, MPlatformLowLevelAccessPort);

#endif // _ME_WINDOWS_PLATFORM_LOW_LEVEL_ACCESS_PORT_