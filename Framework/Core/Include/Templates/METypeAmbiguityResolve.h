// MEngine type ambiguity resolution macro definitions
#pragma once

#ifndef ME_TYPE_AMBIGUITY
#define ME_TYPE_AMBIGUITY

#include <type_traits>

/**
 * Definitions of functions that have two input arguments of different floating-types
 */
#define RESOLVE_FLOATS_AMBIGUITY_2ARGS(FuncName, CustomOption) FLOATS_2_INNER(FuncName, CustomOption)
#define RESOLVE_FLOATS_AMBIGUITY_2ARGS_CONSTEXPR(FuncName) RESOLVE_FLOATS_AMBIGUITY_2ARGS(FuncName, CONSTEXPR)

/**Macros for the bool version */
#define RESOLVE_FLOATS_PREDICATE_AMBIGUITY_2ARGS(FuncName, CustomOption) FLOATS_TO_TYPE_2_INNER(FuncName, bool, CustomOption)

#define FLOATS_2_INNER(FuncName, CustomOption) \
  FLOATS_TEMPLATE_REQUIREMENT_2() \
  FLOATS_TEMPLATE_FUNCTION_BODY_2(FuncName, CustomOption)

#define FLOATS_TO_TYPE_2_INNER(FuncName, ReturnType, CustomOption) \
  FLOATS_TEMPLATE_REQUIREMENT_2() \
  FLOATS_TO_TYPE_TEMPLATE_FUNCTION_BODY_2(FuncName, ReturnType, CustomOption)

#define FLOATS_TEMPLATE_REQUIREMENT_2() \
    template< \
    typename Arg1, \
    typename Arg2, \
    TEMPLATE_CONDITION_DECLARATION( \
      (std::is_floating_point_v<Arg1> || std::is_floating_point_v<Arg2>) && \
      (!std::is_same_v<Arg1, Arg2>) \
    )> 

#define FLOATS_TEMPLATE_FUNCTION_BODY_2(FuncName, CustomOption) \
  CustomOption auto FuncName(IN Arg1 A, IN Arg2 B) -> decltype(A * B) \
  { \
    TYPEDEF(decltype(A * B), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B)); \
  }

#define FLOATS_TO_TYPE_TEMPLATE_FUNCTION_BODY_2(FuncName, ReturnType, CustomOption) \
  CustomOption ReturnType FuncName(IN Arg1 A, IN Arg2 B) \
  { \
    TYPEDEF(decltype(A * B), ArgType); \
    return FuncName(static_cast<ArgType>(A), static_cast<ArgType>(B)); \
  }

/**
 * Definitions of functions that have three input arguments of different floating-types
 */ 
#define RESOLVE_FLOATS_AMBIGUITY_3ARGS(FuncName, CustomOption) FLOATS_3_INNER(FuncName, CustomOption)
#define RESOLVE_FLOATS_AMBIGUITY_3ARGS_CONSTEXPR(FuncName) RESOLVE_FLOATS_AMBIGUITY_3ARGS(FuncName, CONSTEXPR)

/**Macros for the bool version */
#define RESOLVE_FLOATS_PREDICATE_AMBIGUITY_3ARGS(FuncName, CustomOption) FLOATS_TO_TYPE_3_INNER(FuncName, bool, CustomOption)

#define FLOATS_3_INNER(FuncName, CustomOption) \
  FLOATS_TEMPLATE_REQUIREMENT_3() \
  FLOATS_TEMPLATE_FUNCTION_BODY_3(FuncName, CustomOption)

#define FLOATS_TO_TYPE_3_INNER(FuncName, ReturnType, CustomOption) \
  FLOATS_TEMPLATE_REQUIREMENT_3() \
  FLOATS_TO_TYPE_TEMPLATE_FUNCTION_BODY_3(FuncName, ReturnType, CustomOption)

#define FLOATS_TEMPLATE_REQUIREMENT_3() \
  template< \
  typename Arg1, \
  typename Arg2, \
  typename Arg3, \
  TEMPLATE_CONDITION_DECLARATION( \
    (std::is_floating_point_v<Arg1> || std::is_floating_point_v<Arg2> || std::is_floating_point_v<Arg3>) && \
    (!std::is_same_v<Arg1, Arg2> || !std::is_same_v<Arg2, Arg3> || !std::is_same_v<Arg3, Arg1>) \
  )>

#define FLOATS_TEMPLATE_FUNCTION_BODY_3(FuncName, CustomOption) \
  CustomOption auto FuncName(IN Arg1 A, IN Arg2 B, IN Arg3 C) -> decltype(A * B * C) \
  { \
    TYPEDEF(decltype(A * B * C), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B), static_cast<ResultType>(C)); \
  }

#define FLOATS_TO_TYPE_TEMPLATE_FUNCTION_BODY_3(FuncName, ReturnType, CustomOption) \
  CustomOption ReturnType FuncName(IN Arg1 A, IN Arg2 B, IN Arg3 C) \
  { \
    TYPEDEF(decltype(A * B * C), ArgType); \
    return FuncName(static_cast<ArgType>(A), static_cast<ArgType>(B), static_cast<ArgType>(C)); \
  }

/**
 * Definitions of functions that have two input arguments of different integer types
 */
#define RESOLVE_SIGNED_INTS_AMBIGUITY_2ARGS(FuncName, CustomOption) SIGNED_INTS_2_INNER(FuncName, CustomOption)
#define RESOLVE_SIGNED_INTS_AMBIGUITY_2ARGS_CONSTEXPR(FuncName) RESOLVE_SIGNED_INTS_AMBIGUITY_2ARGS(FuncName, CONSTEXPR)

#define SIGNED_INTS_2_INNER(FuncName, CustomOption) \
  SIGNED_INTS_TEMPLATE_REQUIREMENT_2() \
  SIGNED_INTS_TEMPLATE_FUNCTION_BODY_2(FuncName, CustomOption)

#define SIGNED_INTS_TEMPLATE_REQUIREMENT_2() \
  template< \
    typename Arg1, \
    typename Arg2, \
    TEMPLATE_CONDITION_DECLARATION( \
      (std::is_signed_v<Arg1> && std::is_signed_v<Arg2>) && \
      (std::is_integral_v<Arg1> && std::is_integral_v<Arg2>) && \
      (!std::is_same_v<Arg1, Arg2>) \
    )>

#define SIGNED_INTS_TEMPLATE_FUNCTION_BODY_2(FuncName, CustomOption) \
  CustomOption auto FuncName(IN Arg1 A, IN Arg2 B) -> decltype(A * B) \
  { \
    TYPEDEF(decltype(A * B), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B)); \
  }

/**
 * Definitions of functions that have three input arguments of different integer types
 */
#define RESOLVE_SIGNED_INTS_AMBIGUITY_3(FuncName, CustomOption) SIGNED_INTS_3_INNER(FuncName, CustomOption)
#define RESOLVE_SIGNED_INTS_AMBIGUITY_3_CONSTEXPR(FuncName) RESOLVE_SIGNED_INTS_AMBIGUITY_3(FuncName, CONSTEXPR)

#define SIGNED_INTS_3_INNER(FuncName, CustomOption) \
  SIGNED_INTS_TEMPLATE_REQUIREMENT_3() \
  SIGNED_INTS_TEMPLATE_FUNCTION_BODY_3(FuncName, CustomOption)

#define SIGNED_INTS_TEMPLATE_REQUIREMENT_3() \
  template< \
    typename Arg1, \
    typename Arg2, \
    typename Arg3, \
    TEMPLATE_CONDITION_DECLARATION( \
      (std::is_signed_v<Arg1> && std::is_signed_v<Arg2> && std::is_signed_v<Arg3>) && \
      (std::is_integral_v<Arg1> && std::is_integral_v<Arg2> && std::is_integral_v<Arg3>) && \
      (!std::is_same_v<Arg1, Arg2> || !std::is_same_v<Arg2, Arg3> || !std::is_same_v<Arg3, Arg1>) \
    )>

#define SIGNED_INTS_TEMPLATE_FUNCTION_BODY_3(FuncName, CustomOption) \
  CustomOption auto FuncName(IN Arg1 A, IN Arg2 B, IN Arg3 C) -> decltype(A * B * C) \
  { \
    TYPEDEF(decltype(A * B * C), ResultType); \
    return FuncName(static_cast<ResultType>(A), static_cast<ResultType>(B), static_cast<ResultType>(C)); \
  }

#endif // ME_TYPE_AMBIGUITY