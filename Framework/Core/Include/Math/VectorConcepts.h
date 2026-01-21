#pragma once

#ifndef _ME_CORE_MATH_VECTORCONCEPTS_
#define _ME_CORE_MATH_VECTORCONCEPTS_

#include "CoreDefines.h"

#if CAN_USE_CONCEPT

#include "Templates/IsAtLeast32BitIntTypeTraits.h"

#include <type_traits>
#include <concepts>

namespace MEngine
{

namespace Math
{

template<typename IntegerType>
concept IntVectorConcept = MEngine::TypeTraits::IsAtLeast32BitInt_V<IntegerType>;

} // namespace MEngine::Math

} // namespace MEngine

#define Int_Vector_Requirement(IntegerType) requires MEngine::Math::IntVectorConcept<IntegerType>

#endif // CAN_USE_CONCEPT

#ifndef Int_Vector_Requirement
#define Int_Vector_Requirement(Dummy)
#endif

#endif // _ME_CORE_MATH_VECTORCONCEPTS_