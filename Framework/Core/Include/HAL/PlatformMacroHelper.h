#pragma once

#ifndef _ME_PLATFORM_MACRO_HELPER_
#define _ME_PLATFORM_MACRO_HELPER_

#if _WIN32
  #define POSIX_FIX(FunctionCall) _ ## FunctionCall
#else
  #define POSIX_FIX(FunctionCall) FunctionCall
#endif

#endif // _ME_PLATFORM_MACRO_HELPER_