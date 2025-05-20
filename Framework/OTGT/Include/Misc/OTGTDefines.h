#pragma once

#ifndef OTGT_DEFINES
#define OTGT_DEFINES

#include <cassert>

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#endif // #ifndef DLLEXPORT

#ifdef OTGT_EXPORT
#define OTGT_API DLLEXPORT
#else
#define OTGT_API DLLIMPORT
#endif

#endif