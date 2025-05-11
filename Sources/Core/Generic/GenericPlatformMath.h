#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_GENERIC_MATH
#define MENGINE_GENERIC_MATH

namespace MEngine
{
  namespace Math
  {
    struct MGenericPlatformMath
    {
      /**
       * Computes absolute value
       */
      template<typename Type>
      static constexpr FORCEINLINE Type Abs(const Type& Val)
      {
        return (Val < static_cast<Type>(0)) ? -Val : Val;
      } 
    };
  }
}

#endif // MENGINE_GENERIC_MATH