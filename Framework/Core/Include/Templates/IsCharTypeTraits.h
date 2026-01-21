#pragma once

#ifndef _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_
#define _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_

#include "CoreDefines.h"

namespace
{
  template<typename CharType>
  constexpr bool IsCharTypeImpl()
  {
    if constexpr(std::is_same_v<CharType, ANSICHAR>)
    {
      return true;
    }
    else if constexpr(std::is_same_v<CharType, WIDECHAR>)
    {
      return true;
    }
    else if constexpr(std::is_same_v<CharType, UTF8CHAR>)
    {
      return true;
    }
    else if constexpr(std::is_same_v<CharType, UTF16CHAR>)
    {
      return true;
    }    
    else if constexpr(std::is_same_v<CharType, UTF32CHAR>)
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
  template<typename CharType>
  constexpr inline bool IsCharType_V = IsCharTypeImpl<std::remove_cvref_t<CharType>>();
} // namespace MEngine::TypeTraits
} // namespace MEngine

#endif // _ME_CORE_TEMPLATES_IS_CHAR_TYPE_TRAITS_