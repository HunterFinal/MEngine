#pragma once

#ifndef ME_TEMPLATES
#define ME_TEMPLATES

#include "CoreDefines.h"
#include <type_traits>

/**
 * Use to create prvalue without modify source lvalue
 */
template<typename T>
FORCEINLINE std::decay_t<T> CopyTemp(IN T&& Source) noexcept(std::is_nothrow_constructible_v<std::decay_t<T>, T&&>)
{
  return std::forward<T>(Source);
}

template<typename T>
FORCEINLINE auto CopyTempIfNecessary(IN T&& Source)
{
  if constexpr (std::is_lvalue_reference_v<T&&>)
  {
    return CopyTemp(Source);
  }
  else
  {
    return std::move(Source);
  }
}

#endif // ME_TEMPLATES