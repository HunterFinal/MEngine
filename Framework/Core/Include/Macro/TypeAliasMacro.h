// MEngine type alias macro definitions
#pragma once

#ifndef _ME_TYPE_ALIAS_
#define _ME_TYPE_ALIAS_

#include "Macro/CPPVerMacro.h"

#if HAS_CPP_11
  #define TYPEDEF(OldType, NewType) using NewType = OldType;         
#else
  #define TYPEDEF(OldType, NewType) typedef OldType NewType;
#endif  // HAS_CPP_11

#endif // _ME_TYPE_ALIAS_