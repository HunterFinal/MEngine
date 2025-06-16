#pragma once

#ifndef _ME_TYPE_CAST_
#define _ME_TYPE_CAST_

#include "Misc/CoreDefines.h"

#include <type_traits>

template<typename EnumType>
FORCEINLINE constexpr auto EnumCast(EnumType Enum)
{
  static_assert(std::is_integral<typename std::underlying_type<EnumType>::type>::value, "Can not use non-enum type");
  return static_cast<std::underlying_type<EnumType>::type>(Enum);
}

template<typename TypeTo, typename TypeFrom>
FORCEINLINE constexpr TypeTo StaticCast(TypeFrom&& Obj)
{
  return static_cast<TypeTo>(std::forward<TypeFrom>(Obj));
}

#endif // _ME_TYPE_CAST_