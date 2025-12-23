#pragma once

#ifndef _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_
#define _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_

#include "CoreDefines.h"

namespace MEngine
{
  namespace TypeTraits
  {
    template<typename CharType>
    struct IsCharType;

    template<typename CharType>
    struct IsCharType
    {
      static constexpr bool Value = false;
    };

    /**
     * Character type template specialization
     */   
    // Start of Character type template specialization
    #pragma region Character type template specialization
    template<>
    struct IsCharType<ANSICHAR>
    {
      static constexpr bool Value = true;
    };

    template<>
    struct IsCharType<WIDECHAR>
    {
      static constexpr bool Value = true;
    };

    template<>
    struct IsCharType<UTF8CHAR>
    {
      static constexpr bool Value = true;
    };

    template<>
    struct IsCharType<UTF16CHAR>
    {
      static constexpr bool Value = true;
    };

    template<>
    struct IsCharType<UTF32CHAR>
    {
      static constexpr bool Value = true;
    };
    #pragma endregion Character type template specialization
    // End of Character type template specialization

    template<typename CharType>
    struct IsCharType<const CharType>
    {
      static constexpr bool Value = IsCharType<CharType>::Value;
    };

    template<typename CharType>
    struct IsCharType<volatile CharType>
    {
      static constexpr bool Value = IsCharType<CharType>::Value;
    };

    template<typename CharType>
    struct IsCharType<const volatile CharType>
    {
      static constexpr bool Value = IsCharType<CharType>::Value;
    };

    template<typename CharType>
    constexpr inline bool IsCharType_V = IsCharType<CharType>::Value;

  }
}

#endif // _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_