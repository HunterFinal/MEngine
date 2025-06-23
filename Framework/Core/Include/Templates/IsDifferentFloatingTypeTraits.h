#pragma once

#ifndef _ME_CORE_TEMPLATES_IS_DIFFERENT_FLOATING_TYPE_TRAITS_
#define _ME_CORE_TEMPLATES_IS_DIFFERENT_FLOATING_TYPE_TRAITS_

#include <type_traits>

namespace
{
  template<typename T1, typename T2>
  constexpr bool IsDifferentFloatingTypeImpl()
  {
    if constexpr (   (std::is_floating_point_v<T1> && std::is_floating_point_v<T2>)
                  && !std::is_same_v<T1, T2>
                 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

namespace MEngine
{
  namespace TypeTraits
  {
    template<typename T1, typename T2>
    struct IsDifferentFloatingType
    {
      static_assert(std::is_floating_point_v<T1> || std::is_floating_point_v<T2>, "Type is not floating type");

      static constexpr bool Value = IsDifferentFloatingTypeImpl<T1, T2>();
    };

    template<typename T1, typename T2>
    constexpr bool IsDifferentFloatingType_V = IsDifferentFloatingType<T1, T2>::Value;

  }
}

#endif // _ME_CORE_TEMPLATES_IS_DIFFERENT_FLOATING_TYPE_TRAITS_