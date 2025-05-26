// MEngine core definitions
#pragma once

#ifndef MISC_CORE_DEFINES
#define MISC_CORE_DEFINES

#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"

#ifdef CORE_EXPORT
#define CORE_API DLLEXPORT
#else
#define CORE_API DLLIMPORT
#endif

// variables signature
#ifndef IN
  #define IN
#endif // IN
#ifndef OUT
  #define OUT
#endif // OUT
#ifndef DEFAULT_VAR
  #define DEFAULT_VAR
#endif // DEFAULT_VAR

namespace MEngine
{
  // Forward declaration
  struct IEventListener;
  namespace Core
  {

  }

}

TYPEDEF(MEngine::IEventListener, IEventListener);

#endif // MISC_CORE_DEFINES