// MEngine math forward declaration header

#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_MATH_FWD 
#define MENGINE_MATH_FWD

#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"

// Template types forward declarations
namespace MEngine::Math
{
  template<typename T> struct MVector;
}

// Concrete types forward declarations

TYPEDEF(MEngine::Math::MVector<double>, Vector3);
TYPEDEF(MEngine::Math::MVector<float>, Vector3f);

#endif // MENGINE_MATH_FWD