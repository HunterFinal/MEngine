// MEngine windows platform math definitions
#pragma once

#ifndef _ME_CORE_WINDOWS_PLATFORM_MATH_
#define _ME_CORE_WINDOWS_PLATFORM_MATH_

#include "Generic/GenericPlatformMath.h"

namespace MEngine
{
  namespace Math
  {
    struct MWindowsPlatformMath : public MGenericPlatformMath
    {
      // TODO Add Windows specific math method later

      TEMPLATE_REQUIRES_DEFINITION(FLOATING_TYPE_CONCEPT FloatingType, std::is_floating_point_v<FloatingType>)
      FORCEINLINE static bool IsNaN(FloatingType A)
      {
        return std::isnan(A);
      }

      TEMPLATE_REQUIRES_DEFINITION(FLOATING_TYPE_CONCEPT FloatingType, std::is_floating_point_v<FloatingType>)
      FORCEINLINE static bool IsFinite(FloatingType A)
      {
        return std::isfinite(A);
      }
    };
  }
}

TYPEDEF(MEngine::Math::MWindowsPlatformMath, MPlatformMath);

#endif // _ME_CORE_WINDOWS_PLATFORM_MATH_