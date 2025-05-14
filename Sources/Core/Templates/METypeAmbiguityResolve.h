// MEngine type ambiguity resolution macro definitions

#ifdef _WIN32
#pragma once
#endif

#ifndef ME_TYPE_AMBIGUITY
#define ME_TYPE_AMBIGUITY

#include <type_traits>

/**
 * Definitions of functions that have two input arguments of different floating-types
 */
#define RESOLVE_FLOATS_AMBIGUITY_2(FuncName, ...) FLOATS_2_INNER(FuncName, __VA_ARGS__)
#define RESOLVE_FLOATS_AMBIGUITY_2_CONSTEXPR(FuncName) RESOLVE_FLOATS_AMBIGUITY_2(FuncName, CONSTEXPR)

#define FLOATS_2_INNER(FuncName, ...) \
  FLOATS_TEMPLATE_REQUIREMENT_2() \
  FLOATS_TEMPLATE_FUNCTION_BODY_2(FuncName, __VA_ARGS__)

#define FLOATS_TEMPLATE_REQUIREMENT_2() \
    template< \
    typename Arg1, \
    typename Arg2, \
    TEMPLATE_CONDITION( \
      (std::is_floating_point_v<Arg1> && std::is_floating_point_v<Arg2>) && \
      (!std::is_same_v<Arg1, Arg2>) \
    )> 

#define FLOATS_TEMPLATE_FUNCTION_BODY_2(FuncName, ...) \
  static __VA_ARGS__ auto FuncName(IN Arg1 A, IN Arg2 B) -> decltype(A * B) \
  { \
    TYPEDEF(decltype(A * B), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B)); \
  }

/**
 * Definitions of functions that have two input arguments of different integer types
 */
#define RESOLVE_SIGNED_INTS_AMBIGUITY_2(FuncName, ...) SIGNED_INTS_2_INNER(FuncName, __VA_ARGS__)
#define RESOLVE_SIGNED_INTS_AMBIGUITY_2_CONSTEXPR(FuncName) RESOLVE_SIGNED_INTS_AMBIGUITY_2(FuncName, CONSTEXPR)

#define SIGNED_INTS_2_INNER(FuncName, ...) \
  SIGNED_INTS_TEMPLATE_REQUIREMENT_2() \
  SIGNED_INTS_TEMPLATE_FUNCTION_BODY_2(FuncName, __VA_ARGS__)

#define SIGNED_INTS_TEMPLATE_REQUIREMENT_2() \
  template< \
    typename Arg1, \
    typename Arg2, \
    TEMPLATE_CONDITION( \
      (std::is_signed_v<Arg1> && std::is_signed_v<Arg2>) && \
      (std::is_integral_v<Arg1> && std::is_integral_v<Arg2>) && \
      (!std::is_same_v<Arg1, Arg2>) \
    )>

#define SIGNED_INTS_TEMPLATE_FUNCTION_BODY_2(FuncName, ...) \
  static __VA_ARGS__ auto FuncName(IN Arg1 A, IN Arg2 B) -> decltype(A * B) \
  { \
    TYPEDEF(decltype(A * B), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B)); \
  }

#endif // ME_TYPE_AMBIGUITY