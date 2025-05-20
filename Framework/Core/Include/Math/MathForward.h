// MEngine math forward declaration header
#pragma once

#ifndef MENGINE_MATH_FWD 
#define MENGINE_MATH_FWD

#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"

// Template types forward declarations
namespace MEngine::Math
{
  template<typename T> struct MVector;
  template<typename T> struct MVector2D;
}

// Concrete types forward declarations

TYPEDEF(MEngine::Math::MVector<double>, Vector3);     
TYPEDEF(MEngine::Math::MVector<float>, Vector3f);     
TYPEDEF(MEngine::Math::MVector<float>, Vector3F);                          
TYPEDEF(MEngine::Math::MVector2D<double>, Vector2);
TYPEDEF(MEngine::Math::MVector2D<float>, Vector2f);
TYPEDEF(MEngine::Math::MVector2D<float>, Vector2F);

#endif // MENGINE_MATH_FWD