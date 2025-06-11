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
    };
  }
}

TYPEDEF(MEngine::Math::MWindowsPlatformMath, MPlatformMath);

#endif // _ME_CORE_WINDOWS_PLATFORM_MATH_