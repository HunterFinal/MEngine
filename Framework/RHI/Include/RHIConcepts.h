#pragma once

#ifndef _ME_RHI_CONCEPTS_
#define _ME_RHI_CONCEPTS_

#include "CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"

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

#endif // CAN_USE_CONCEPT

#ifndef Requires_RHICommand_Callable
  #define Requires_RHICommand_Callable(CmdListType, LambdaType)
#endif



#endif // _ME_RHI_CONCEPTS_
