#pragma once

#ifndef ME_FUNC_PTR_TYPE_TRAITS
#define ME_FUNC_PTR_TYPE_TRAITS

#include "Macro/TypeAliasMacro.h"

/**
 * Type traits for class member function
 */
template<bool IsConst, typename Class, typename FuncType>
struct ClassMemberFuncPtrType;

/**
 * class member function type without const
 */
template<typename Class, typename ReturnType, typename... ArgTypes>
struct ClassMemberFuncPtrType<false, Class, ReturnType(ArgTypes...)>
{
  TYPEDEF(ReturnType (Class::*)(ArgTypes...), Type);
};

/**
 * class member function type with const
 */
template<typename Class, typename ReturnType, typename... ArgTypes>
struct ClassMemberFuncPtrType<true, Class, ReturnType(ArgTypes...)>
{
  TYPEDEF(ReturnType (Class::*)(ArgTypes...) const, Type);
};

#endif // ME_FUNC_PTR_TYPE_TRAITS