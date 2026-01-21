#pragma once 

#ifndef _ME_CORE_MATH_INTVECTOR2_
#define _ME_CORE_MATH_INTVECTOR2_

#include "CoreDefines.h"
#include "MathForward.h"
#include "VectorConcepts.h"

namespace MEngine
{

namespace Math
{

template<typename IntegerType>
Int_Vector_Requirement(IntegerType)
struct MIntVector2
{

  #if !CAN_USE_CONCEPT
    static_assert(std::is_integral_v<IntegerType>, "Only integer types are supported");
    static_assert(sizeof(IntegerType) >= 4, "Integer type size of IntVector2 must equal or greater than 32 bit");
  #endif

  union
  {
    struct
    {
      // x-coordinate of vector
      IntegerType X;

      // y-coordinate of vector
      IntegerType Y;
    };

    IntegerType XY[2];
  };

  CORE_API static const MIntVector2<IntegerType> ZeroVector;

  FORCEINLINE static MIntVector2<IntegerType> Zero()
  {
    return ZeroVector;
  }

  constexpr MIntVector2()
    : X{0}
    , Y{0}
  {}

  FORCEINLINE MIntVector2(IN IntegerType InX, IN IntegerType InY);

};

} // namespace MEngine::Math

} // namespace MEngine

// Only include inline implement file here
#include "Math/IntVector2.inl"

#endif // _ME_CORE_MATH_INTVECTOR2_