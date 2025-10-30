// MEngine coordinate axis enum definition
#pragma once

#ifndef _ME_CORE_MATH_AXIS_
#define _ME_CORE_MATH_AXIS_

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
  } // namespace MEngine::Math
} // namespace MEngine

#endif // _ME_CORE_MATH_AXIS_