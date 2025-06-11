#pragma once

#ifndef _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_
#define _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_

#include "Misc/CoreDefines.h"
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
    };
  }
}

TYPEDEF(MEngine::Core::MWindowsPlatformStringUtility, MPlatformStringUtility)

#endif // _ME_CORE_WINDOWS_PLATFORM_STRING_UTILITY_