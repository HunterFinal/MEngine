// MEngine assertion macro definitions
#pragma once

#ifndef _ME_ASSERTION_MACROS_
#define _ME_ASSERTION_MACROS_

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

#endif // _ME_ASSERTION_MACROS_