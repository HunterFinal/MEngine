#pragma once

#ifndef _ME_CORE_MATH_MATRIX_4X4_
#define _ME_CORE_MATH_MATRIX_4X4_

#include "Math/Vector.h"
#include "Misc/CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"

namespace MEngine
{
  namespace Math
  {
    template<FLOATING_TYPE_CONCEPT FloatingType, uint32 AlignSize = 16>
    struct alignas(AlignSize) MMatrix4x4
    {
      #if !CAN_USE_CONCEPT
        static_assert(std::is_floating_point_v<FloatingType>, "Type of Matrix4x4 must be floating point");
      #endif

      public:
        TYPEDEF(FloatingType, Type);
        GENERATE_CLASS_DEF(MMatrix4x4<FloatingType, AlignSize>);

        alignas(AlignSize) Type Matrix[4][4];

        CORE_API static const MMatrix4x4<FloatingType, AlignSize> Identity;

        /**
         * Constructors
         */

        /**
         * Default constructor
         */
        FORCEINLINE explicit MMatrix4x4();

        /**
         * Construct matrix with Vector3
         */
        FORCEINLINE MMatrix4x4(IN const MVector<Type>& V1, IN const MVector<Type>& V2, IN const MVector<Type>& V3, IN const MVector<Type>& V4);

        // End constructors

        /**
         * Set this Matrix to identity
         */

         FORCEINLINE void SetIdentity
    };
  }
}

#endif // _ME_CORE_MATH_MATRIX_4X4_