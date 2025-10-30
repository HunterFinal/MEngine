// MEngine math forward declaration header
#pragma once

#ifndef _ME_CORE_MATH_FWD_ 
#define _ME_CORE_MATH_FWD_

#include "HAL/Platform.h"
#include "Macro/TypeAliasMacro.h"
#include "Misc/ConceptsStoragePlace.h"

// Template types forward declarations
namespace MEngine::Math
{
  template<typename T> struct MVector;
  template<typename T> struct MVector2D;
  template<FLOATING_TYPE_CONCEPT T, uint32 AlignSize> struct alignas(AlignSize) MVector4;
  template<FLOATING_TYPE_CONCEPT T, uint32 AlignSize> struct alignas(AlignSize) MMatrix4x4;
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

#define COMMA ,

// 16-alignment Vector4
TYPEDEF(MEngine::Math::MVector4<double COMMA 16>, Vector4D);
TYPEDEF(MEngine::Math::MVector4<double COMMA 16>, Vector4d);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4F);
TYPEDEF(MEngine::Math::MVector4<float COMMA 16>, Vector4f);

// 16-alignment Matrix
TYPEDEF(MEngine::Math::MMatrix4x4<double COMMA 16>, Matrix44d);
TYPEDEF(MEngine::Math::MMatrix4x4<double COMMA 16>, Matrix44D);
TYPEDEF(MEngine::Math::MMatrix4x4<float COMMA 16>, Matrix44);
TYPEDEF(MEngine::Math::MMatrix4x4<float COMMA 16>, Matrix44f);
TYPEDEF(MEngine::Math::MMatrix4x4<float COMMA 16>, Matrix44F);

#undef COMMA

#endif // _ME_CORE_MATH_FWD_