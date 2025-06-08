// MEngine assertion macro definitions
#pragma once

#ifndef _ME_ASSERTION_MACROS_
#define _ME_ASSERTION_MACROS_

#include "Debug/Debugger.h"
#include "HAL/Platform.h"
#include "Macro/GenericMacroDefines.h"

#include <cstdlib>

#ifndef ABORT_ASSERT_INTERNAL
  #if ME_DO_ABORT
    #define ABORT_ASSERT_INTERNAL() abort();
  #else
    #define ABORT_ASSERT_INTERNAL() ME_EMPTY_MACRO_EXPR;
  #endif
#endif
  
#if ME_DO_CHECK
  #define me_assert(expr) ME_EMPTY_MACRO_EXPR
#else
  #define me_assert(expr) me_assert_impl(!!(expr))
#endif

#define me_assert_impl(expr) \
    do \
    { \
      if (!(expr)) UNLIKELY \
      { \
        if (MDebugger::GetGDebugger().Func()) \
        { \
          PLATFORM_BREAK(); \
          ABORT_ASSERT_INTERNAL(); \
        } \
      } \
    } while(0);

#endif // _ME_ASSERTION_MACROS_