#pragma once

#ifndef _ME_CORE_TEMPLATES_IS_CHAR_FIXED_WIDTH_TYPE_TRAITS_
#define _ME_CORE_TEMPLATES_IS_CHAR_FIXED_WIDTH_TYPE_TRAITS_

#include "CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Templates/IsCharTypeTraits.h"

#include <type_traits>

namespace
{
  template<CHAR_TYPE_CONCEPT Encoding>
  constexpr bool IsCharFixedWidthImpl()
  {
    return 
      std::is_same_v<Encoding, ANSICHAR>  ||
      std::is_same_v<Encoding, WIDECHAR>  ||
      std::is_same_v<Encoding, UTF16CHAR> ||
      std::is_same_v<Encoding, UTF32CHAR> ;
  }
} // nameless namespace

namespace MEngine
{
  namespace TypeTraits
  {
    template<CHAR_TYPE_CONCEPT Encoding>
    struct IsCharFixedWidth
    {
      #if !CAN_USE_CONCEPT
      static_assert(IsCharType<Encoding>, "Encoding type is not a valid character type");
      #endif

      static constexpr bool Value = IsCharFixedWidthImpl<Encoding>();
    };

    template<CHAR_TYPE_CONCEPT Encoding>
    inline constexpr bool IsCharFixedWidth_V = IsCharFixedWidth<Encoding>::Value;
  }
}

#endif // _ME_CORE_TEMPLATES_IS_CHAR_FIXED_WIDTH_TYPE_TRAITS_