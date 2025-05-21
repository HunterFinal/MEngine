// MEngine generic platform math class
#pragma once

#ifndef MENGINE_GENERIC_MATH
#define MENGINE_GENERIC_MATH

#include "Templates/METypeAmbiguityResolve.h"
#include "Templates/METypeTraits.h"
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
      NODISCARD_MSG("Ignoring return value of Abs") static CONSTEXPR FORCEINLINE Type Abs(IN const Type Val)
      {
        return (Val < static_cast<Type>(0)) ? -Val : Val;
      }

      /**
       * Returns -1, 0 or 1 depending on sign of value
       * 
       * @param Val Input value
       * @return -1 if value less than 0, 0 if value is equal to 0, 1 otherwise
       */
      template<typename Type>
      NODISCARD_MSG("Ignoring return value of Sign") static CONSTEXPR FORCEINLINE Type Sign(IN const Type Val)
      {
        const Type positive = static_cast<Type>(1);
        const Type zero = static_cast<Type>(0);
        const Type negative = static_cast<Type>(-1);

        return ((Val < zero) ? negative : ((Val > zero) ? positive : zero));
      }

      /**
       * Get the bigger value of two values
       * 
       * @param Val1 The first value
       * @param Val2 The second value
       * @return The bigger value 
       */
      template<typename Type>
      NODISCARD_MSG("Ignoring return value of Max") static CONSTEXPR FORCEINLINE Type Max(IN const Type Val1, IN const Type Val2)
      {
        return (Val1 > Val2) ? Val1 : Val2;
      }
      RESOLVE_FLOATS_AMBIGUITY_2ARGS(Max, NODISCARD_MSG("Ignoring return value of Max") static CONSTEXPR);
      RESOLVE_SIGNED_INTS_AMBIGUITY_2ARGS(Max, NODISCARD_MSG("Ignoring return value of Max") static CONSTEXPR);
      
      /**
       * Get the smaller value of two values
       * 
       * @param Val1 The first value
       * @param Val2 The second value
       * @return The smaller value 
       */
      template<typename Type>
      NODISCARD_MSG("Ignoring return value of Min") static CONSTEXPR FORCEINLINE Type Min(IN const Type Val1, IN const Type Val2)
      {
        return (Val1 < Val2) ? Val1 : Val2;
      }
      RESOLVE_FLOATS_AMBIGUITY_2ARGS(Min, NODISCARD_MSG("Ignoring return value of Min") static CONSTEXPR);
      RESOLVE_SIGNED_INTS_AMBIGUITY_2ARGS(Min, NODISCARD_MSG("Ignoring return value of Min") static CONSTEXPR);

      /**
       * Clamps value to be between Min and Max([Min,Max],inclusive)
       * 
       * @param Value value to clamp
       * @param MinVal value of Min
       * @param MaxVal value of Max
       * @return The value between Min and Max
       */
      template<typename Type>
      NODISCARD_MSG("Ignoring return value of Clamp") static CONSTEXPR FORCEINLINE Type Clamp(IN const Type Value, 
                                                                                              IN const Type MinVal, 
                                                                                              IN const Type MaxVal)
      {
        return Max(Min(Value, MaxVal), MinVal);
      }
      RESOLVE_FLOATS_AMBIGUITY_3ARGS(Clamp, NODISCARD_MSG("Ignoring return value of Clamp") static constexpr);

      /**
       * Converts a floating-type num to an integer with truncation towards zero
       * 
       * @param Val Value to convert
       * @return Truncated integer
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int32 TruncToInt32(IN const Type Val)
      {
        return static_cast<int32>(Val);
      }

      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int64 TruncToInt64(IN const Type Val)
      {
        return static_cast<int64>(Val);
      }

      static CONSTEXPR FORCEINLINE int32 TruncToInt(IN const float Val)
      {
        return TruncToInt32(Val);
      }

      static CONSTEXPR FORCEINLINE int64 TruncToInt(IN const double Val)
      {
        return TruncToInt64(Val);
      }

      /**Integer version of Trunc */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_integral_v<Type>)>
      static CONSTEXPR FORCEINLINE Type Trunc(IN const Type Val)
      {
        return Val;
      }

      static FORCEINLINE float Trunc(IN const float Val) { return std::truncf(Val); }
      static FORCEINLINE double Trunc(IN const double Val) { return std::trunc(Val); }
      static FORCEINLINE long double Trunc(IN const long double Val) { return std::truncl(Val); }

      /**
       * Converts a floating-type num to the nearest greater or equal integer
       * 
       * @param Val Value to convert
       * @return An integer greater or equal to "Val"
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int32 CeilToInt32(IN const Type Val)
      {
        int32 ceilResult = static_cast<int32>(Val);
        ceilResult += static_cast<int32>(static_cast<Type>(ceilResult) < Val);
        return ceilResult;
      }

      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int64 CeilToInt64(IN const Type Val)
      {
        int64 ceilResult = static_cast<int64>(Val);
        ceilResult += static_cast<int64>(static_cast<Type>(ceilResult) < Val);
        return ceilResult;
      }

      static CONSTEXPR FORCEINLINE int32 CeilToInt(IN const float Val) { return CeilToInt32(Val); }
      static CONSTEXPR FORCEINLINE int64 CeilToInt(IN const double Val) { return CeilToInt64(Val); }
      
      /**Integer version of Ceil */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_integral_v<Type>)>
      static CONSTEXPR FORCEINLINE Type Ceil(IN const Type Val) { return Val; }

      static FORCEINLINE float Ceil(IN const float Val) { return std::ceilf(Val); }
      static FORCEINLINE double Ceil(IN const double Val) { return std::ceil(Val); }
      static FORCEINLINE long double Ceil(IN const long double Val) { return std::ceill(Val); }

      /**
       * Converts a floating-type num to the nearest less or equal integer
       * 
       * @param Val Value to convert
       * @return An integer less or equal to "Val"
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int32 FloorToInt32(IN const Type Val)
      {
        int32 floorResult = static_cast<int32>(Val);
        floorResult -= static_cast<int32>(static_cast<Type>(floorResult) < Val);
        return floorResult;
      }

      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int64 FloorToInt64(IN const Type Val)
      {
        int64 floorResult = static_cast<int64>(Val);
        floorResult -= static_cast<int64>(static_cast<Type>(floorResult) < Val);
        return floorResult;
      }

      static CONSTEXPR FORCEINLINE int32 FloorToInt(IN const float Val) { return FloorToInt32(Val); }
      static CONSTEXPR FORCEINLINE int64 FloorToInt(IN const double Val) { return FloorToInt64(Val); }

      /**Integer version of Floor */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_integral_v<Type>)>
      static CONSTEXPR FORCEINLINE Type Floor(IN const Type Val) { return Val; }

      static FORCEINLINE float Floor(IN const float Val) { return std::floorf(Val); }
      static FORCEINLINE double Floor(IN const double Val) { return std::floor(Val); }
      static FORCEINLINE long double Floor(IN const long double Val) { return std::floorl(Val); }

      /**
       * Converts a floating-type num to the nearest integer. Rounds up when the fraction is .5
       * 
       * @param Val Value to convert
       * @return The nearest integer to "Val"
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int32 RoundToInt32(IN const Type Val)
      {
        return FloorToInt32(Val + static_cast<Type>(0.5));
      }

      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE int64 RoundToInt64(IN const Type Val)
      {
        return FloorToInt64(Val + static_cast<Type>(0.5));
      }
      
      static CONSTEXPR FORCEINLINE int32 RoundToInt(IN const float Val) { return RoundToInt32(Val); }
      static CONSTEXPR FORCEINLINE int64 RoundToInt(IN const double Val) { return RoundToInt64(Val); }

      /**Integer version of Round */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_integral_v<Type>)>
      static CONSTEXPR FORCEINLINE Type Round(IN const Type Val) { return Val;}

      static FORCEINLINE float Round(IN const float Val) { return std::roundf(Val); }
      static FORCEINLINE double Round(IN const double Val) { return std::round(Val); }
      static FORCEINLINE long double Round(IN const long double Val) { return std::roundl(Val); }

      /**
       * Get signed fractional part of a floating-type value
       * 
       * @param Val Floating-type value to convert
       * @return A float between [0, 1) for positive input. A float between (-1 0] for negative input
       */
      template<typename Type, TEMPLATE_CONDITION_DECLARATION(std::is_floating_point_v<Type>)>
      static CONSTEXPR FORCEINLINE Type Fraction(IN const Type Val)
      {
        return Val - Trunc(Val);
      }

      static FORCEINLINE float Sqrt(IN const float Val)  { return std::sqrtf(Val); }
      static FORCEINLINE double Sqrt(IN const double Val) { return std::sqrt(Val);  }
      static FORCEINLINE long double Sqrt(IN const long double Val) { return std::sqrtl(Val); }

      static FORCEINLINE float Pow(IN const float Base, IN const float Exponent) { return std::powf(Base, Exponent); }
      static FORCEINLINE double Pow(IN const double Base, IN const double Exponent) { return std::pow(Base, Exponent); }
      static FORCEINLINE long double Pow(IN const long double Base, IN const long double Exponent) { return std::powl(Base, Exponent); }
      RESOLVE_FLOATS_AMBIGUITY_2ARGS(Pow, static CONSTEXPR);

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
        return std::asinl(validVal); 
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
        return std::acosl(validVal); 
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