// MEngine core definitions
#pragma once

#ifndef _ME_CORE_DEFINES_
#define _ME_CORE_DEFINES_

#include "BuildDefines.h"
#include "HAL/Platform.h"
#include "Macro/CPPVerMacro.h"
#include "Macro/ClassMacroHelpers.h"
#include "Macro/StandardMacros.h"
#include "Macro/TypeAliasMacro.h"
#include "Templates/METypeTraits.h"

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

// MEngine specific macro
#define _MENGINE_VER CONCAT(_ME_VER_MAJ,_ME_VER_MIN)

#define CONCAT(x, y) x ## y
#define _ME_VER_MAJ 1
#define _ME_VER_MIN 0
#undef CONCAT


#endif // _ME_CORE_DEFINES_