// MEngine HAL platform
#pragma once

#ifndef MENGINE_HAL_PLATFORM
#define MENGINE_HAL_PLATFORM

// TODO Should not include this here;
#include "HAL/PlatformHeader.h"

#include "HAL/PreprocessorHelpers.h"

// Platform macro definitions
// Make other platform macro definitions to 0
#if !defined(PLATFORM_WINDOWS)
  #define PLATFORM_WINDOWS 0
#endif
#if !defined(PLATFORM_LINUX)
  #define PLATFORM_LINUX 0
#endif
#if !defined(PLATFORM_MAC)
  #define PLATFORM_MAC 0
#endif
#if !defined(PLATFORM_MICROSOFT)
  #define PLATFORM_MICROSOFT 0
#endif

// Include platform setup header
// XXX/XXXPlatform.h
#include PLATFORM_HEADER(Platform.h)


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
// The switchable char. Either ANSICHAR or WIDECHAR
TYPEDEF(MPlatformTypes::TCHAR, TCHAR);
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

// indicate that something unused
#if !defined(MAYBE_UNUSED) && defined(__has_cpp_attribute)
  #if __has_cpp_attribute(maybe_unused)
    #define MAYBE_UNUSED [[maybe_unused]]
  #endif //  __has_cpp_attribute(maybe_unused)
#endif // !defined(MAYBE_UNUSED) && defined(__has_cpp_attribute)
#ifndef MAYBE_UNUSED
  #define MAYBE_UNUSED
#endif

/**
 * indicate that allow the compiler to optimize for the case where paths of execution including
 * that statement are more or less likely than any alternative path of execution that does not include such a statement
 * // URL: https://en.cppreference.com/w/cpp/language/attributes/likely
 */
#if !defined(LIKELY) && defined(__has_cpp_attribute)
  #ifdef likely
    #undef likely
  #endif

  #if __has_cpp_attribute(likely)
    #if HAS_CPP_20
      #define LIKELY [[likely]]
    #else
      #define LIKELY
    #endif // HAS_CPP_20
  #endif // __has_cpp_attribute(likely)
#endif // !defined(LIKELY) && defined(__has_cpp_attribute)
#ifndef LIKELY
  #define LIKELY
#endif // LIKELY

#if (defined(__clang__) || defined(__GNUC__))
  #define LIKELY_EXPR(expr) __builtin_except(!!(expr), 1)
#else
  #define LIKELY_EXPR(expr) !!(expr)
#endif // (defined(__clang__) || defined(__GNUC__))

#if !defined(UNLIKELY) && defined(__has_cpp_attribute)
  #ifdef unlikely
    #undef unlikely
  #endif

  #if __has_cpp_attribute(unlikely)
    #if HAS_CPP_20
      #define UNLIKELY [[unlikely]]
    #else
      #define UNLIKELY
    #endif // HAS_CPP_20
  #endif // __has_cpp_attribute(likely)
#endif // !defined(UNLIKELY) && defined(__has_cpp_attribute)
#ifndef UNLIKELY
  #define UNLIKELY
#endif // UNLIKELY

#if (defined(__clang__) || defined(__GNUC__))
  #define UNLIKELY_EXPR(expr) __builtin_except(!!(expr), 0)
#else
  #define UNLIKELY_EXPR(expr) !!(expr)
#endif // (defined(__clang__) || defined(__GNUC__))

#endif // MENGINE_HAL_PLATFORM