// MEngine math utility class definitions
#pragma once

#ifndef MENGINE_MATH_UTILITY
#define MENGINE_MATH_UTILITY

#include "HAL/Platform.h"
#include "HAL/PlatformMath.h"
#include "Macro/CPPVerMacro.h"

namespace MEngine
{
  namespace Math
  {
    struct MMath : public MPlatformMath
    {
      // Constant Definitions
      #if HAS_CPP_17
        // Float
        inline static constexpr float PI =                          (3.1415926535897932384626433832795f);
        inline static constexpr float FLOAT_TOLERANCE_SMALL =       (1.e-8f);
        inline static constexpr float FLOAT_TOLERANCE_KINDA_SMALL = (1.e-4f);
        inline static constexpr float BIG_NUMBER =                  (3.4e+38f);
        inline static constexpr float EULERS_NUMBER =               (2.71828182845904523536f);
        inline static constexpr float MAX_FLOAT =                   (3.402823466e+38f); // same as FLT_MAX in float.h
        inline static constexpr float RAD_2_DEG =                   (57.29577951308233f);
        inline static constexpr float DEG_2_RAD =                   (0.0174532925199433f);

        // Double
        inline static constexpr double DOUBLE_PI =                    (3.1415926535897932384626433832795);
        inline static constexpr double DOUBLE_TOLERANCE_SMALL =       (1.e-8);
        inline static constexpr double DOUBLE_TOLERANCE_KINDA_SMALL = (1.e-4);
        inline static constexpr double DOUBLE_BIG_NUMBER =            (3.4e+38);
        inline static constexpr double DOUBLE_EULERS_NUMBER =         (2.71828182845904523536);
        inline static constexpr double MAX_DOUBLE =                   (1.7976931348623158e+308); // same as DBL_MAX in float.h
        inline static constexpr double DOUBLE_RAD_2_DEG =             (57.29577951308233);
        inline static constexpr double DOUBLE_DEG_2_RAD =             (0.0174532925199433);

        // Vector
        inline static constexpr float VECTOR_NORMALIZED_THRESHOLD  =  (0.001f);
      #else
        // Float
        static const float PI;
        static const float FLOAT_TOLERANCE_SMALL;
        static const float FLOAT_TOLERANCE_KINDA_SMALL;
        static const float BIG_NUMBER;
        static const float EULERS_NUMBER;
        static const float MAX_FLOAT; // same as FLT_MAX in float.h
        static const float RAD_2_DEG;
        static const float DEG_2_RAD;

        // Double
        static const double DOUBLE_PI;
        static const double DOUBLE_TOLERANCE_SMALL;
        static const double DOUBLE_TOLERANCE_KINDA_SMALL;
        static const double DOUBLE_BIG_NUMBER;
        static const double DOUBLE_EULERS_NUMBER;
        static const double MAX_DOUBLE; // same as DBL_MAX in float.h
        static const double DOUBLE_RAD_2_DEG;
        static const double DOUBLE_DEG_2_RAD;

        // Vector
        static const float VECTOR_NORMALIZED_THRESHOLD;
      #endif // HAS_CPP_17
      
      /**
       * Check two floating-type values for equality within tolerance
       * 
       * @param Val1 The first value
       * @param Val2 The second value
       * @param Tolerance Error tolerance
       * @return true if two values are equal within tolerance limits, false otherwise
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE bool IsNearlyEquals(IN const Type Val1, IN const Type Val2, DEFAULT_VAR const Type Tolerance = (Type)DOUBLE_TOLERANCE_SMALL);

      RESOLVE_FLOATS_PREDICATE_AMBIGUITY_3ARGS(IsNearlyEquals, static CONSTEXPR);

      /**
       * Check floating-type input value is nearly zero within tolerance
       * 
       * @param Val The input value
       * @param Tolerance Error tolerance
       * @return true if "Val" is nearly zero within tolerance limits, false otherwise
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE bool IsNearlyZero(IN const Type Val, IN const Type Tolerance = (Type)DOUBLE_TOLERANCE_SMALL);
    };

    template<typename Type, TEMPLATE_CONDITION_DEFINITION(std::is_floating_point_v<Type>)>
    CONSTEXPR FORCEINLINE bool MMath::IsNearlyEquals(IN const Type Val1, IN const Type Val2, DEFAULT_VAR const Type Tolerance)
    {
      return Abs<Type>(Val1 - Val2) <= Tolerance;
    }

    template<typename Type, TEMPLATE_CONDITION_DEFINITION(std::is_floating_point_v<Type>)>
    static CONSTEXPR FORCEINLINE bool MMath::IsNearlyZero(IN const Type Val, IN const Type Tolerance)
    {
      return Abs<Type>(Val) <= Tolerance;
    }

  }
}

// Math class alias
TYPEDEF(MEngine::Math::MMath, MMath);

#endif // MENGINE_MATH_UTILITY