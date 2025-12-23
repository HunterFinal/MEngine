#pragma once

#ifndef _ME_TYPE_CAST_
#define _ME_TYPE_CAST_

#include "CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"
#include <type_traits>

template<ENUM_TYPE_CONCEPT EnumType>
FORCEINLINE constexpr auto EnumCast(EnumType Enum)
{
  #if !CAN_USE_CONCEPT
  static_assert(std::is_enum<EnumType>::value, "Can not use non-enum type");
  #endif
  return static_cast<std::underlying_type<EnumType>::type>(Enum);
}

template<typename TypeTo, typename TypeFrom>
FORCEINLINE constexpr TypeTo StaticCast(TypeFrom&& Obj)
{
  return static_cast<TypeTo>(std::forward<TypeFrom>(Obj));
}

#endif // _ME_TYPE_CAST_