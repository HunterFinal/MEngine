#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_PLATFORM_WINDOWS
#define MENGINE_PLATFORM_WINDOWS

#include "Generic/GenericTypeDefines.h"

#if defined(_MSC_VER)
#include <intrin.h>     // __nop()
#endif

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

// DLL export and import definitions
// 動的ライブラリマクロ定義
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

// Function type macros
// 関数種類マクロ定義

// Force function as inline
#define FORCEINLINE __forceinline
// Force function as not inline
#define FORCENOINLINE __declspec(noinline)

// TODO
// Unknown macros(need research)
#undef USE_UTF8_CHAR
#define USE_UTF8_CHAR 0

// TODO
// __nop() before __debugbreak()
#define PLATFORM_BREAK() \
  { \
    __nop(), __debugbreak(); \
  } 
#endif // MENGINE_PLATFORM_WINDOWS