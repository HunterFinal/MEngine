#pragma once

#ifndef _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_
#define _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_

#include "CoreDefines.h"
#include "Generic/GenericPlatformStringUtility.h"

namespace MEngine
{
  namespace Core
  {
    struct MWindowsPlatformStringUtility : public MGenericPlatformStringUtility
    {
      CORE_API static SIZE_T Strlen(IN const ANSICHAR* Str);
      CORE_API static SIZE_T Strlen(IN const WIDECHAR* Str);
      CORE_API static SIZE_T Strlen(IN const UTF8CHAR* Str);
      CORE_API static WIDECHAR* Strcpy(
        OUT WIDECHAR* Dest, 
        IN const WIDECHAR* Src, 
        IN const SIZE_T DestCount);

      CORE_API static int32 PrintBufferV(
        IN WIDECHAR* BufferAddress,
        IN const SIZE_T BufferSize,
        IN const WIDECHAR* Format,
        IN va_list Args);
        
      CORE_API static int32 PrintBufferV(
        IN ANSICHAR* BufferAddress,
        IN const SIZE_T BufferSize,
        IN const ANSICHAR* Format,
        IN va_list Args);
      
    };
  }
}

TYPEDEF(MEngine::Core::MWindowsPlatformStringUtility, MPlatformStringUtility)

#endif // _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_