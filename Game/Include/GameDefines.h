#pragma once

#ifndef GAME_DEFINES
#define GAME_DEFINES

#ifdef GAME_DLL_BUILD
  #define GAME_API __declspec(dllexport)
#else 
  #define GAME_API __declspec(dllimport)
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

#endif // GAME_DEFINES