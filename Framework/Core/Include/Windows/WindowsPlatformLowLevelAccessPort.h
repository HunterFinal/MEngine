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

      static CORE_API void* GetDllLibrary(IN const TCHAR* Filename);
      static CORE_API void UnloadDllLibrary(IN void* Handle);

      static CORE_API const TCHAR* GetBaseDir();

      static CORE_API uint32 GetLastError();
      static CORE_API void SetLastError(IN uint32 ErrorCode);
      static CORE_API const TCHAR* ConvertSystemErrorMessage(IN TCHAR* Buffer, IN uint32 BufferSize, IN uint32 ErrorCode);
    };
  }
}

TYPEDEF(MEngine::Core::MWindowsPlatformLowLevelAccessPort, MPlatformLowLevelAccessPort);

#endif // _ME_WINDOWS_PLATFORM_LOW_LEVEL_ACCESS_PORT_