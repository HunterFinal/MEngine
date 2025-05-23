#pragma once

#ifndef ME_APP_DEFINES
#define ME_APP_DEFINES

#include "FunctionSymbolHelpers.h"

#ifdef APP_DLL_BUILD
#define APP_API __declspec(dllexport)
#else
#define APP_API __declspec(dllimport)
#endif // APP_DLL_BUILD

#ifndef FORCEINLINE
  #define FORCEINLINE __forceinline
#endif
#ifndef FORCENOINLINE
  #define FORCENOINLINE __declspec(noinline)
#endif

#ifndef IN
  #define IN
#endif
#ifndef OUT
  #define OUT
#endif
#ifndef DEFAULT_VAR
  #define DEFAULT_VAR
#endif


#endif // ME_APP_DEFINES