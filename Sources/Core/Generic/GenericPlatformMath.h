// MEngine generic platform math class

#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_GENERIC_MATH
#define MENGINE_GENERIC_MATH

#include <cmath>
#include "Templates/METypeAmbiguityResolve.h"

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
      static CONSTEXPR FORCEINLINE Type Abs(IN const Type Val)
      {
        return (Val < static_cast<Type>(0)) ? -Val : Val;
      }

      /**
       * Get the bigger value of two values
       * 
       * @param Val1 The first value
       * @param Val2 The second value
       * @return The bigger value 
       */
      template<typename Type>
      static CONSTEXPR FORCEINLINE Type Max(IN const Type Val1, IN const Type Val2)
      {
        return (Val1 > Val2) ? Val1 : Val2;
      }
      RESOLVE_FLOATS_AMBIGUITY_2_CONSTEXPR(Max);
      RESOLVE_SIGNED_INTS_AMBIGUITY_2_CONSTEXPR(Max);
      
      /**
       * Get the smaller value of two values
       * 
       * @param Val1 The first value
       * @param Val2 The second value
       * @return The smaller value 
       */
      template<typename Type>
      static CONSTEXPR FORCEINLINE Type Min(IN const Type Val1, IN const Type Val2)
      {
        return (Val1 < Val2) ? Val1 : Val2;
      }
      RESOLVE_FLOATS_AMBIGUITY_2_CONSTEXPR(Min);
      RESOLVE_SIGNED_INTS_AMBIGUITY_2_CONSTEXPR(Min);
      
      static FORCEINLINE float Ceil(IN const float Val) { return std::ceilf(Val); }
      static FORCEINLINE double Ceil(IN const double Val) { return std::ceil(Val); }
      static FORCEINLINE long double Ceil(IN const long double Val) { return std::ceill(Val); }

      static FORCEINLINE float Sqrt(IN const float Val)  { return std::sqrtf(Val); }
      static FORCEINLINE double Sqrt(IN const double Val) { return std::sqrt(Val);  }
      static FORCEINLINE long double Sqrt(IN const long double Val) { return std::sqrtl(Val); }

      static FORCEINLINE float Pow(IN const float Base, IN const float Exponent) { return std::powf(Base, Exponent); }
      static FORCEINLINE double Pow(IN const double Base, IN const double Exponent) { return std::pow(Base, Exponent); }
      static FORCEINLINE long double Pow(IN const long double Base, IN const long double Exponent) { return std::powl(Base, Exponent); }
      RESOLVE_FLOATS_AMBIGUITY_2_CONSTEXPR(Pow);

      /**
       * Trigonometric functions
       */
      static FORCEINLINE float Sin(IN const float Val) { return std::sinf(Val); }
      static FORCEINLINE double Sin(IN const double Val) { return std::sin(Val); }
      static FORCEINLINE long double Sin(IN const long double Val) { return std::sinl(Val); }

      static FORCEINLINE float Cos(IN const float Val) { return std::cosf(Val); }
      static FORCEINLINE double Cos(IN const double Val) { return std::cos(Val); }
      static FORCEINLINE long double Cos(IN const long double Val) { return std::cosl(Val); }

      static FORCEINLINE float Tan(IN const float Val) { return std::tanf(Val); }
      static FORCEINLINE double Tan(IN const double Val) { return std::tan(Val); }
      static FORCEINLINE long double Tan(IN const long double Val) { return std::tanl(Val); }

      static FORCEINLINE float ASin(IN const float Val) 
      { 
        const float validVal = (Val < -1.0f) ? -1.0f : ((Val > 1.0f) ? 1.0f : Val);
        return std::asinf(validVal); 
      }
      static FORCEINLINE double ASin(IN const double Val)
      { 
        const double validVal = (Val < -1.0) ? -1.0 : ((Val > 1.0) ? 1.0 : Val);
        return std::asin(validVal); 
      }
      static FORCEINLINE long double ASin(IN const long double Val) 
      { 
        const long double validVal = (Val < -1.0l) ? -1.0l : ((Val > 1.0l) ? 1.0l : Val);
        return std::asinl(Val); 
      }

      static FORCEINLINE float ACos(IN const float Val) 
      { 
        const float validVal = (Val < -1.0f) ? -1.0f : ((Val > 1.0f) ? 1.0f : Val);
        return std::acosf(validVal); 
      }
      static FORCEINLINE double ACos(IN const double Val)
      { 
        const double validVal = (Val < -1.0) ? -1.0 : ((Val > 1.0) ? 1.0 : Val);
        return std::acos(validVal); 
      }
      static FORCEINLINE long double ACos(IN const long double Val) 
      { 
        const long double validVal = (Val < -1.0l) ? -1.0l : ((Val > 1.0l) ? 1.0l : Val);
        return std::acosl(Val); 
      }

      static FORCEINLINE float ATan(IN const float Val) { return std::atanf(Val); }
      static FORCEINLINE double ATan(IN const double Val) { return std::atan(Val); }
      static FORCEINLINE long double ATan(IN const long double Val) { return std::atanl(Val); }
    };
 
    /**
     *  Template specialization
     */ 
    template<> FORCEINLINE float MGenericPlatformMath::Abs(IN const float Val)
    {
      return std::fabsf(Val);
    }

    template<> FORCEINLINE double MGenericPlatformMath::Abs(IN const double Val)
    {
      return std::fabs(Val);
    }

    template<> FORCEINLINE long double MGenericPlatformMath::Abs(IN const long double Val)
    {
      return std::fabsl(Val);
    }
  }
}

#endif // MENGINE_GENERIC_MATH