#pragma once

#ifndef _ME_RUNTIME_ECSCORE_CORE_BITLIB_
#define _ME_RUNTIME_ECSCORE_CORE_BITLIB_

#include "CoreDefines.h"

#include <type_traits>
#if HAS_CPP_20
#include <bit>
#endif

namespace MEngine
{

namespace ECSCore
{
  template<typename ValueType>
  static CONSTEXPR SIZE_T PopCountInternal(IN const ValueType InValue)
  {
    if (InValue == 0)
    {
      return 0;
    }

    return static_cast<SIZE_T>(InValue & 0b1) + PopCountInternal(static_cast<SIZE_T>(InValue >> 1));
  }

  template<typename ValueType>
  FORCEINLINE CONSTEXPR SIZE_T PopCount(IN const ValueType InValue)
  {
    static_assert(std::is_unsigned_v<ValueType>, "Can not use PopCount if ValueType is not unsigned");
    #if HAS_CPP_20
    return std::popcount(InValue);
    #else
    return PopCountInternal(InValue);
    #endif
  }

} // namespace MEngine::ECSCore

} // namespace MEngine

#endif // _ME_RUNTIME_ECSCORE_CORE_BITLIB_