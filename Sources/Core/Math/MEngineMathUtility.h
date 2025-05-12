#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_MATH_UTILITY
#define MENGINE_MATH_UTILITY

#include "HAL/Platform.h"
#include "HAL/PlatformMath.h"

namespace MEngine
{
  namespace Math
  {
    struct MMath : public MPlatformMath
    {
      // Constant Definitions
      // Float
      static constexpr float PI =                          (3.1415926535897932384626433832795f);
      static constexpr float FLOAT_TOLERANCE_SMALL =       (1.e-8f);
      static constexpr float FLOAT_TOLERANCE_KINDA_SMALL = (1.e-4f);
      static constexpr float BIG_NUMBER =                  (3.4e+38f);
      static constexpr float EULERS_NUMBER =               (2.71828182845904523536f);
      static constexpr float MAX_FLOAT =                   (3.402823466e+38f); // same as FLT_MAX in float.h
      static constexpr float RAD_2_DEG =                   (57.29577951308233f);
      static constexpr float DEG_2_RAD =                   (0.0174532925199433f);

      // Double
      static constexpr double DOUBLE_PI =                    (3.1415926535897932384626433832795);
      static constexpr double DOUBLE_TOLERANCE_SMALL =       (1.e-8);
      static constexpr double DOUBLE_TOLERANCE_KINDA_SMALL = (1.e-4);
      static constexpr double DOUBLE_BIG_NUMBER =            (3.4e+38);
      static constexpr double DOUBLE_EULERS_NUMBER =         (2.71828182845904523536);
      static constexpr double MAX_DOUBLE =                   (1.7976931348623158e+308); // same as DBL_MAX in float.h
      static constexpr double DOUBLE_RAD_2_DEG =             (57.29577951308233);
      static constexpr double DOUBLE_DEG_2_RAD =             (0.0174532925199433);

      // Vector
      static constexpr float VECTOR_NORMALIZED_THRESHOLD  =  (0.001f);
    };
  }
}

// Math class alias
TYPEDEF(MEngine::Math::MMath, MMath);

#endif // MENGINE_MATH_UTILITY