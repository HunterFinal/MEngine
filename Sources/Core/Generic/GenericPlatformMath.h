#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_GENERIC_MATH
#define MENGINE_GENERIC_MATH

#include <cmath>

namespace MEngine
{
  namespace Math
  {
    struct MGenericPlatformMath
    {
      /**
       * Computes absolute value
       * 
       * @param Val The origin value
       * @return The absolute value of origin
       */
      template<typename Type>
      static constexpr FORCEINLINE Type Abs(Type Val)
      {
        return (Val < static_cast<Type>(0)) ? -Val : Val;
      }
      
      static FORCEINLINE float Sqrt(float Val)
      {
        return std::sqrtf(Val);
      }
      static FORCEINLINE double Sqrt(double Val)
      {
        return std::sqrt(Val);
      }
    };
  }
}

#endif // MENGINE_GENERIC_MATH