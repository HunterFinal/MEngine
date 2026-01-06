#pragma once

#ifndef _ME_RHI_HELPER_
#define _ME_RHI_HELPER_

#include "CoreDefines.h"
#include "RHIDefines.h"
#include "RHITypes.h"

namespace MEngine
{

namespace RHI
{
  struct MRHIHelper
  {
    RHI_API static uint32 GetVertexCountOfPrimitiveType(IN uint32 PrimitiveNum, IN MEngine::RHI::EPrimitiveTopologyType PrimitiveType);
  };
} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::MRHIHelper, RHIHelper);

#endif // _ME_RHI_HELPER_