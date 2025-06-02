#pragma once

#ifndef _ME_TYPE_CAST_
#define _ME_TYPE_CAST_

#include "Macro/CPPVerMacro.h"
#include "Misc/CoreDefines.h"

#include <cassert>
#include <type_traits>

template<typename EnumType>
FORCEINLINE constexpr auto EnumCast(EnumType Enum)
{
  #if HAS_CPP_14
    static_assert(std::is_integral_v<std::underlying_type_t<EnumType>>, "Can not use non-enum type");
    return static_cast<std::underlying_type_t<EnumType>>(Enum);
  #else
    static_assert(std::is_integral<typename std::underlying_type<EnumType>::type>::value, "Can not use non-enum type");
    return static_cast<std::underlying_type<EnumType>::type>(Enum);
  #endif
}

template<typename TypeTo, typename TypeFrom>
FORCEINLINE constexpr TypeTo StaticCast(TypeFrom&& Obj)
{
  return static_cast<TypeTo>(std::forward<TypeFrom>(Obj));
}

#endif // _ME_TYPE_CAST_