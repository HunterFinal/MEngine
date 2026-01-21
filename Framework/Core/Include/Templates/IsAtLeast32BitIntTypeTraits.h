#pragma once

#ifndef _ME_CORE_TEMPLATES_ATLEAST32BITINT_TYPETRAITS_
#define _ME_CORE_TEMPLATES_ATLEAST32BITINT_TYPETRAITS_

#include "CoreDefines.h"
#include <type_traits>

namespace
{

template<typename IntegerType>
static constexpr bool IsAtLeast32BitIntImpl()
{
  if constexpr(std::is_integral_v<IntegerType> && sizeof(IntegerType) >= 4)
  {
    return true;
  }
  else
  {
    return false;
  }
}

} // nameless namespace

namespace MEngine
{

namespace TypeTraits
{

template<typename IntegerType>
struct IsAtLeast32BitInt
{
  static constexpr bool Value = IsAtLeast32BitIntImpl<IntegerType>();
};

template<typename IntegerType>
constexpr inline bool IsAtLeast32BitInt_V = IsAtLeast32BitInt<IntegerType>::Value;

} // namespace MEngine::TypeTraits

} // namespace MEngine

#endif // _ME_CORE_TEMPLATES_ATLEAST32BITINT_TYPETRAITS_