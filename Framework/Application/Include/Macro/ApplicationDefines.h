#pragma once

#ifndef _ME_APP_APPLICATION_DEFINES_
#define _ME_APP_APPLICATION_DEFINES_

#include "CoreDefines.h"

#ifdef APP_EXPORT
#define APP_API DLLEXPORT
#else
#define APP_API DLLIMPORT
#endif // APP_EXPORT

#ifndef FORCEINLINE
  #define FORCEINLINE __forceinline
#endif
#ifndef FORCENOINLINE
  #define FORCENOINLINE __declspec(noinline)
#endif

#endif // _ME_APP_APPLICATION_DEFINES_