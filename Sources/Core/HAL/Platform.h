#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_HAL_PLATFORM
#define MENGINE_HAL_PLATFORM

#include "HAL/PreprocessorHelpers.h"

#include PLATFORM_HEADER(Platform.h)

// DLL export and import definitions
#ifndef DLLEXPORT
  #define DLLEXPORT
  #define DLLIMPORT
#endif // DLLEXPORT

//~Global types base

// 8-bit unsigned integer
TYPEDEF(MPlatformTypes::uint8, uint8);
// 16-bit unsigned integer
TYPEDEF(MPlatformTypes::uint16, uint16);
// 32-bit unsigned integer
TYPEDEF(MPlatformTypes::uint32, uint32);
// 64-bit unsigned integer
TYPEDEF(MPlatformTypes::uint64, uint64);
// 8-bit signed integer
TYPEDEF(MPlatformTypes::int8, int8);
// 16-bit signed integer
TYPEDEF(MPlatformTypes::int16, int16);
// 32-bit signed integer
TYPEDEF(MPlatformTypes::int32, int32);
// 64-bit signed integer
TYPEDEF(MPlatformTypes::int64, int64);
// 7-bit character(8-bit fixed)
TYPEDEF(MPlatformTypes::ANSICHAR, ANSICHAR);
// ?-bit character(depends on platform)
TYPEDEF(MPlatformTypes::WIDECHAR, WIDECHAR);
// Unicode 8-bit character
TYPEDEF(MPlatformTypes::UTF8CHAR, UTF8CHAR);
// Unicode 16-bit character
TYPEDEF(MPlatformTypes::UTF16CHAR, UTF16CHAR);
// Unicode 32-bit character
TYPEDEF(MPlatformTypes::UTF32CHAR, UTF32CHAR);

TYPEDEF(MPlatformTypes::SIZE_T, SIZE_T);

TYPEDEF(MPlatformTypes::SSIZE_T, SSIZE_T);
// NULL type
TYPEDEF(MPlatformTypes::TYPE_NULL, TYPE_NULL);
// nullptr type
TYPEDEF(MPlatformTypes::TYPE_NULLPTR, TYPE_NULLPTR);

// ------------
// TEXT macros
// ------------
#ifndef PLATFORM_WIDECHAR_IS_CHAR16
  #define PLATFORM_WIDECHAR_IS_CHAR16  0
#endif // PLATFORM_WIDECHAR_IS_CHAR16
#ifndef PLATFORM_CHAR_IS_UTF8CHAR
  #define PLATFORM_CHAR_IS_UTF8CHAR    USE_UTF8_CHAR
#endif // PLATFORM_CHAR_IS_UTF8CHAR

#define UTF8TEXT_INNER(x) u8 ## x
#define UTF16TEXT_INNER(x) u ## x
#if PLATFORM_WIDECHAR_IS_CHAR16
  #define WIDETEXT_INNER(x) UTF16TEXT_INNER(x)
#else
  #define WIDETEXT_INNER(x) L ## x
#endif // #if PLATFORM_WIDECHAR_IS_CHAR16

#if !defined(MTEXT)
  #if PLATFORM_CHAR_IS_UTF8CHAR
    #define TEXT_INNER(x) UTF8TEXT_INNER(x)
  #else
    #define TEXT_INNER(x) WIDETEXT_INNER(x)
  #endif // #if PLATFORM_CHAR_IS_UTF8CHAR
  #define MTEXT(x) TEXT_INNER(x)
#endif // !defined(MTEXT)

// ----------------------
// Function type macros
// ----------------------
#ifndef FORCEINLINE
  #define FORCEINLINE
#endif // FORCEINLINE
#ifndef FORCENOINLINE
  #define FORCENOINLINE
#endif // FORCENOINLINE

// Warn function callers should not ignore return value;
#if !defined(NODISCARD) && defined(__has_cpp_attribute)
  #if __has_cpp_attribute(nodiscard)
    #define NODISCARD [[nodiscard]]
  #endif // __has_cpp_attribute(nodiscard)
#endif // !defined(NODISCARD) && defined(__has_cpp_attribute)
#ifndef NODISCARD
  #define NODISCARD
#endif // NODISCARD

// Warn function callers should not ignore return value(specific message)
#if !defined(NODISCARD_MSG) && defined(__has_cpp_attribute)
  #if __has_cpp_attribute(nodiscard)
    #if HAS_CPP_20 && (defined(_MSC_VER) && (_MSC_VER >= 1928) || (defined(__clang__) && __clang_major__ >= 10))
      #define NODISCARD_MSG(Msg) [[nodiscard(Msg)]]
    #endif // HAS_CPP_20 && (defined(_MSC_VER) && (_MSC_VER >= 1928) || (defined(__clang__) && __clang_major__ >= 10))
  #endif // __has_cpp_attribute(nodiscard)
#endif // !defined(NODISCARD_MSG) && defined(__has_cpp_attribute)
#ifndef NODISCARD_MSG
  #define NODISCARD_MSG(Msg)
#endif // NODISCARD_MSG

// Use NODISCARD_CTOR on constructors instead of NODISCARD
// Older compilers don't support [[nodiscard]] on constructors
#if !defined(NODISCARD_CTOR) && defined(__has_cpp_attribute)
  #if __has_cpp_attribute(nodiscard)
    #if (defined(_MSC_VER) && _MSC_VER >= 1928) || (defined(__clang__) && __clang_major__ >= 10) 
      #define NODISCARD_CTOR [[nodiscard]]
    #endif // (defined(_MSC_VER) && _MSC_VER >= 1928) || (defined(__clang__) && __clang_major__ >= 10) 
  #endif // __has_cpp_attribute(nodiscard)
#endif // !defined(NODISCARD_CTOR) && defined(__has_cpp_attribute)
#ifndef NODISCARD_CTOR
  #define NODISCARD_CTOR
#endif

// indicate function callers that never returns
#if !defined(NORETURN) && defined(__has_cpp_attribute)
  #if __has_cpp_attribute(noreturn)
    #define NORETURN [[noreturn]]
  #endif // __has_cpp_attribute(noreturn)
#endif // !defined(NORETURN) && defined(__has_cpp_attribute)
#ifndef NORETURN
  #define NORETURN
#endif // NORETURN

// variables signature
#ifndef IN
#define IN
#endif // IN
#ifndef OUT
#define OUT
#endif // OUT
#ifndef DEFAULT_VAR
#define DEFAULT_VAR
#endif // DEFAULT_VAR

#endif // MENGINE_HAL_PLATFORM