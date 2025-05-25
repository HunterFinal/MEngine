// MEngine type alias macro definitions
#pragma once

#ifndef MENGINE_TYPE_ALIAS
#define MENGINE_TYPE_ALIAS

#include "Macro/CPPVerMacro.h"

#if HAS_CPP_11
  #define TYPEDEF(OldType, NewType) using NewType = OldType;         
#else
  #define TYPEDEF(OldType, NewType) typedef OldType NewType;
#endif  // HAS_CPP_11

#endif // MENGINE_TYPE_ALIAS