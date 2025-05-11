#ifdef _WIN32
#pragma once
#endif


#ifndef MENGINE_TYPE_DEF
#define MENGINE_TYPE_DEF

#include "Macro/TypeAliasMacro.h"

namespace MPlatform
{
  struct MGenericPlatformTypes
  {
    //~ Unsigned base
    //-----------------------------------
      // 8-bit unsigned integer
      TYPEDEF(unsigned char, uint8);

      // 16-bit unsigned integer
      TYPEDEF(unsigned short int, uint16);

      // 32-bit unsigned integer
      TYPEDEF(unsigned int, uint32);

      // 64-bit unsigned integer
      TYPEDEF(unsigned long long, uint64);
    //-----------------------------------

    //~ Signed base
    //-----------------------------------
      // 8-bit signed integer
      TYPEDEF(signed char, int8);

      // 16-bit signed integer
      TYPEDEF(signed short int, int16);

      // 32-bit signed integer
      TYPEDEF(signed int, int32);

      // 64-bit signed integer
      TYPEDEF(signed long long, int64);
    //-----------------------------------

    //~ Character base
    //-----------------------------------
      // ANSI character (7-bit)
      TYPEDEF(char, ANSICHAR);

      // Wide character (?-bit(Depends on Platform))
      TYPEDEF(wchar_t, WIDECHAR);

      // Unicode 8-bit character
      #if HAS_CPP_20
        TYPEDEF(char8_t, UTF8CHAR);
      #else
        enum UTF8CHAR : unsigned char {};
      #endif

      // Unicode 16-bit character
      #if HAS_CPP_11
        TYPEDEF(char16_t, UTF16CHAR);
      #else
        TYPEDEF(uint16, UTF16CHAR);
      #endif

      // Unicode 32-bit character
      #if HAS_CPP_11
        TYPEDEF(char32_t, UTF32CHAR);
      #else
        TYPEDEF(uint32, UTF32CHAR);
      #endif
    //-----------------------------------

    //~ Pointer base
    //-----------------------------------
      // NULL type
      TYPEDEF(int32, TYPE_NULL);

      // nullptr type
      TYPEDEF(decltype(nullptr), TYPE_NULLPTR);
    //-----------------------------------
  };
}

#endif