// MEngine windows platform definitions
#pragma once

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

// TODO
// DONT DEFINE THIS HERE!!!!!!!
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

// constexpr macro
#if defined(__clang__) && (__clang__ >= 304)
  #define CONSTEXPR constexpr
#endif // __clang__
#ifndef CONSTEXPR
  #if defined(__GNUC__) && ((__GNUC__ >= 4) && (__GNUC_MINOR__ >= 9))
    #define CONSTEXPR constexpr
  #endif // __GNUC__
#endif
#ifndef CONSTEXPR
  #if defined(_MSC_VER) && (_MSC_VER >= 1900)
    #define CONSTEXPR constexpr
  #endif // _MSC_VER
#endif
#ifndef CONSTEXPR
  #define CONSTEXPR
#endif

// TODO
// Unknown macros(need research)
#undef USE_UTF8_CHAR
#define USE_UTF8_CHAR 1

// TODO
// __nop() before __debugbreak()
#define PLATFORM_BREAK() \
  { \
    __nop(), __debugbreak(); \
  } 

#endif // MENGINE_PLATFORM_WINDOWS