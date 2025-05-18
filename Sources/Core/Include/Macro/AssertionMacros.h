// MEngine assertion macro definitions

#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_ASSERTION_MACROS
#define MENGINE_ASSERTION_MACROS

#include "HAL/Platform.h"

#if HAS_CPP_20
  #define ME_CHECK_IMPL(expression) \
    { \
      if((!expression)) [[unlikely]] \
      { \
        PLATFORM_BREAK(); \
      } \
    }
#else
  #define ME_CHECK_IMPL(expression) \
  { \
    if((!expression)) \
    { \
      PLATFORM_BREAK(); \
    } \
  }
#endif // !defined(HAS_CPP_20)

#endif // MENGINE_ASSERTION_MACROS