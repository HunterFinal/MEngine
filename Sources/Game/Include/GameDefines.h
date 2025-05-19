#ifdef _WIN32
#pragma once
#endif

#ifndef GAME_DEFINES
#define GAME_DEFINES

#ifdef GAME_DLL_BUILD
  #define GAME_API __declspec(dllexport)
#else 
  #define GAME_API __declspec(dllimport)
#endif

#endif // GAME_DEFINES