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
      static CORE_API bool IsDebuggerPresent();
      static CORE_API void PlatformPrintDebugString(IN const TCHAR* Str);
      static CORE_API void PlatformPrintToLocalDevice(IN const TCHAR* Str);

      static CORE_API uint32 GetLastError();
      static CORE_API void SetLastError(IN uint32 ErrorCode);
      static CORE_API const TCHAR* ConvertSystemErrorMessage(IN TCHAR* Buffer, IN uint32 BufferSize, IN uint32 ErrorCode);

    };
  }
}

#endif // _ME_GENERIC_PLATFORM_LOW_LEVEL_ACCESS_PORT_