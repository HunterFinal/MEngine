// MEngine core definitions
#pragma once

#ifndef MISC_CORE_DEFINES
#define MISC_CORE_DEFINES

#include "Macro/TypeAliasMacro.h"


#ifdef CORE_EXPORT
#define CORE_API DLLEXPORT
#else
#define CORE_API DLLIMPORT
#endif

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