#pragma once

#ifndef _ME_CORE_MACRO_COMPILER_MACRO_
#define _ME_CORE_MACRO_COMPILER_MACRO_

#if defined(__clang__)
  #define ME_IS_CLANG 1
#elif defined(__GNUC__)
  #define ME_IS_GCC 1
#elif defined(_MSC_VER)
  #define ME_IS_MSVC 1
#endif

#ifndef ME_IS_CLANG
  #define ME_IS_CLANG 0
#endif
#ifndef ME_IS_GCC
  #define ME_IS_GCC 0
#endif
#ifndef ME_IS_MSVC
  #define ME_IS_MSVC 0
#endif

#endif // _ME_CORE_MACRO_COMPILER_MACRO_