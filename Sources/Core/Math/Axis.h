// MEngine coordinate axis enum definition

#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_MATH_AXIS
#define MENGINE_MATH_AXIS

namespace MEngine
{
  namespace Math
  {
    /**
     * Enum of coordinate axis
     */
    enum class EAxis
    {
      X = 0,      // Positive x-axis 
      Y,          // Positive y-axis
      Z,          // Positive z-axis
      XNegative,  // Negative x-axis
      YNegative,  // Negative y-axis
      ZNegative,  // Negative z-axis
    };
  }
}

#endif // MENGINE_MATH_AXIS