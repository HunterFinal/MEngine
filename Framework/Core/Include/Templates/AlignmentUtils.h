#pragma once

#ifndef _ME_CORE_ALIGNMENTUTILS_
#define _ME_CORE_ALIGNMENTUTILS_

#include "CoreDefines.h"
#include <type_traits>

namespace MEngine
{

namespace Core
{

#if CAN_USE_CONCEPT
template<typename AlignableType>
concept ValueAlignable = 
  std::is_integral_v<AlignableType> ||
  std::is_pointer_v<AlignableType>;

#define Alignable_Concept MEngine::Core::ValueAlignable

#endif

#ifndef Alignable_Concept
  #define Alignable_Concept typename
#endif

template<Alignable_Concept ValType>
constexpr ValType Align(ValType Val, SIZE_T Alignment)
{
  #if !CAN_USE_CONCEPT
    static_assert(std::is_integral_v<AlignableType> || std::is_pointer_v<AlignableType>, "AlignAny expects an integer or pointer type");
  #endif

  if constexpr (std::is_pointer_v<ValType>)
  {
    return reinterpret_cast<ValType>((reinterpret_cast<SIZE_T>(Val) + Alignment - 1) & ~(Alignment - 1));
  }
  else
  {
    return static_cast<ValType>((static_cast<SIZE_T>(Val) + Alignment - 1) & ~(Alignment - 1));
  }
}

template<Alignable_Concept ValType>
constexpr ValType AlignAny(ValType Val, SIZE_T Alignment)
{
  #if !CAN_USE_CONCEPT
    static_assert(std::is_integral_v<AlignableType> || std::is_pointer_v<AlignableType>, "AlignAny expects an integer or pointer type");
  #endif

  if constexpr (std::is_pointer_v<ValType>)
  {
    return reinterpret_cast<ValType>(((reinterpret_cast<SIZE_T>(Val) + Alignment - 1) / Alignment) * Alignment);
  }
  else
  {
    return static_cast<ValType>(((static_cast<SIZE_T>(Val) + Alignment - 1) / Alignment) * Alignment);
  }
}

} // namespace MEngine::Core

} // namespace MEngine


#endif // _ME_CORE_ALIGNMENTUTILS_