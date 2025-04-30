#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_PLATFORM_WINDOWS
#define MENGINE_PLATFORM_WINDOWS

#include "Type/GenericTypeDefines.h"

namespace MPlatform
{
  struct MWindowsPlatformTypes : public MGenericPlatformTypes
  {
    #ifdef _WIN64
      TYPEDEF(unsigned __int64, SIZE_T);
      TYPEDEF(__int64, SSIZE_T);
    #else
      TYPEDEF(unsigned long, SIZE_T);
      TYPEDEF(long, SSIZE_T);
    #endif
  };
}

TYPEDEF(MPlatform::MWindowsPlatformTypes, MPlatformTypes);

#endif