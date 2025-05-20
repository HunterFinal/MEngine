#ifdef _WIN32
#pragma once
#endif

#ifndef CPP_PRIMITIVE_EXT
#define CPP_PRIMITIVE_EXT

#include <string>

namespace Extensions
{
  /**
   * Convert integer to string
   * 
   * @param Value The integer value
   * @return Converted string
   */
  FORCEINLINE std::string ToString(IN const SIZE_T& Value);
}

#endif