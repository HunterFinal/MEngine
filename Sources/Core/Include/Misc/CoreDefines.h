// MEngine core definitions

#ifdef _WIN32
#pragma once
#endif

#ifndef MISC_CORE_DEFINES
#define MISC_CORE_DEFINES

// IN/OUT 
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#ifdef CORE_EXPORT
#define CORE_API DLLEXPORT
#else
#define CORE_API DLLIMPORT
#endif

namespace MEngine
{
  namespace Core
  {

  }
}

#endif // MISC_CORE_DEFINES