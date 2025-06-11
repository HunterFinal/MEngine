#pragma once

#ifndef _ME_CORE_TEMPLATES_IS_CHAR_ENCODING_COMPATIBLE_TYPE_TRAITS_
#define _ME_CORE_TEMPLATES_IS_CHAR_ENCODING_COMPATIBLE_TYPE_TRAITS_

#include "Misc/CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Templates/IsCharTypeTraits.h"

#include <type_traits>

namespace
{
  template<
    CHAR_TYPE_CONCEPT SourceEncodingType, 
    CHAR_TYPE_CONCEPT DestinationEncodingType
  >
  constexpr bool IsCharEncodingCompatibleImpl()
  {
    if constexpr (std::is_same_v<SourceEncodingType, DestinationEncodingType>)
    {
      return true;
    }
    else if constexpr (std::is_same_v<SourceEncodingType, WIDECHAR> && std::is_same_v<DestinationEncodingType, UTF16CHAR>)
    {
      return true;
    }

    return false;
  }
}

namespace MEngine
{
  namespace TypeTraits
  {
    template<
      CHAR_TYPE_CONCEPT SourceEncodingType, 
      CHAR_TYPE_CONCEPT DestinationEncodingType
    >
    struct IsCharEncodingCompatible
    {
      #if !CAN_USE_CONCEPT
      static_assert(IsCharType_V<SourceEncodingType>,       "Source encoding type is not a valid character type");
      static_assert(IsCharType_V<DestinationEncodingType>,  "Destination encoding type is not a valid character type");
      #endif

      static constexpr bool Value = IsCharEncodingCompatibleImpl<std::remove_cv_t<SourceEncodingType>, std::remove_cv_t<DestinationEncodingType>>();
    };

    template<
      CHAR_TYPE_CONCEPT SourceEncodingType, 
      CHAR_TYPE_CONCEPT DestinationEncodingType
    >
    constexpr inline bool IsCharEncodingCompatible_V = IsCharEncodingCompatible<SourceEncodingType, DestinationEncodingType>::Value;
  }
}

#endif // _ME_CORE_TEMPLATES_IS_CHAR_ENCODING_COMPATIBLE_TYPE_TRAITS_