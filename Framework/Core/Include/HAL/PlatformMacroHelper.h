#pragma once

#ifndef ME_PLATFORM_MACRO_HELPER
#define ME_PLATFORM_MACRO_HELPER

#if _WIN32
  #define POSIX_FIX(FunctionCall) _ ## FunctionCall
#else
  #define POSIX_FIX(FunctionCall) FunctionCall
#endif

#endif // ME_PLATFORM_MACRO_HELPER