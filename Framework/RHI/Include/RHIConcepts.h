#pragma once

#ifndef _ME_RHI_CONCEPTS_
#define _ME_RHI_CONCEPTS_

#include "CoreDefines.h"

#if CAN_USE_CONCEPT
#include <concepts>

namespace MEngine
{

namespace RHI
{

class MRHICommandList;

template<typename RHICmdListType, typename RHICommandLambdaType>
concept RHICommandCallable = 
  std::is_base_of_v<MEngine::RHI::MRHICommandList, RHICmdListType> &&
  requires (RHICommandLambdaType t, RHICmdListType& RHICmdListRef)
  {
    { t.operator()(RHICmdListRef) } -> std::same_as<void>;
  };
}

}

#define Requires_RHICommand_Callable(CmdListType, LambdaType) requires MEngine::RHI::RHICommandCallable<CmdListType, LambdaType>

// FIXME Move this to Core 
#define Requires_Derived_From(DerivedType, BaseType) requires std::derived_from<DerivedType, BaseType>

#endif // CAN_USE_CONCEPT

#ifndef Requires_RHICommand_Callable
  #define Requires_RHICommand_Callable(CmdListType, LambdaType)
#endif

#ifndef Requires_Derived_From
  #define Requires_Derived_From(...)
#endif


#endif // _ME_RHI_CONCEPTS_
