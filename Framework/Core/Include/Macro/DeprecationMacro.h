#pragma once

#ifndef _ME_CORE_MACRO_DEPRECATION_MACRO_
#define _ME_CORE_MACRO_DEPRECATION_MACRO_

#include "Macro/CompilerMacro.h"
#include "Macro/CPPVerMacro.h"

#define ME_DEPRECATED_COMMON_MSG " Please update your code before upgrade to new version."
#define ME_DEPRECATED_MENGINE_HEADER_MSG "Deprecated MEngine version:"
#define DEPRECATED_CAT(Version, Message) ME_DEPRECATED_MENGINE_HEADER_MSG #Version " " Message ME_DEPRECATED_COMMON_MSG

// #if defined(__INTELLISENSE__)
//   #define ME_DEPRECATED(Version, Message)
// #else
  #if (ME_IS_CLANG || ME_IS_GCC)
    #if HAS_CPP_14
      #define ME_DEPRECATED(Version, Message) [[deprecated(DEPRECATED_CAT(Version, Message))]]
    #else
      #define ME_DEPRECATED(Version, Message) __attribute__((deprecated(DEPRECATED_CAT(Version, Message))))
    #endif
  #elif ME_IS_MSVC
    #define ME_DEPRECATED(Version, Message) __declspec(deprecated(DEPRECATED_CAT(Version, Message)))
  #else
    #define ME_DEPRECATED(Version, Message)
  #endif
// #endif // defined(__INTELLISENSE__)

#endif // _ME_CORE_MACRO_DEPRECATION_MACRO_