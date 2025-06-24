// MEngine math forward declaration header
#pragma once

#ifndef MENGINE_MATH_FWD 
#define MENGINE_MATH_FWD

#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"
#include "Misc/ConceptsStoragePlace.h"

// Template types forward declarations
namespace MEngine::Math
{
  template<typename T> struct MVector;
  template<typename T> struct MVector2D;
  template<FLOATING_TYPE_CONCEPT T, uint32 AlignSize> struct alignas(AlignSize) MVector4;
}

// Concrete types forward declarations

TYPEDEF(MEngine::Math::MVector<double>, Vector3D);
TYPEDEF(MEngine::Math::MVector<double>, Vector3d);     
TYPEDEF(MEngine::Math::MVector<float>, Vector3);                             
TYPEDEF(MEngine::Math::MVector<float>, Vector3F);                             
TYPEDEF(MEngine::Math::MVector<float>, Vector3f);                             
TYPEDEF(MEngine::Math::MVector2D<double>, Vector2D);
TYPEDEF(MEngine::Math::MVector2D<double>, Vector2d);
TYPEDEF(MEngine::Math::MVector2D<float>, Vector2);
TYPEDEF(MEngine::Math::MVector2D<float>, Vector2F);
TYPEDEF(MEngine::Math::MVector2D<float>, Vector2f);

// 16-alignment Vector4
#define COMMA ,
TYPEDEF(MEngine::Math::MVector4<double COMMA 16>, Vector4D);
TYPEDEF(MEngine::Math::MVector4<double COMMA 16>, Vector4d);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4F);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4f);
#undef COMMA


#endif // MENGINE_MATH_FWD