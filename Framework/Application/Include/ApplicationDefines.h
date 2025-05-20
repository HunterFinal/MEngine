#ifdef _WIN32
#pragma once
#endif

#ifndef ME_APP_DEFINES
#define ME_APP_DEFINES

#ifdef APP_DLL_BUILD
#define APP_API __declspec(dllexport)
#else
#define APP_API __declspec(dllimport)
#endif // APP_DLL_BUILD

#ifndef FORCEINLINE
  #define FORCEINLINE __forceinline
#endif

#endif // ME_APP_DEFINES