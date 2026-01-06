#pragma once

#ifndef _ME_RHI_PIPELINE_
#define _ME_RHI_PIPELINE_

#include "RHIDefines.h"
#include "Macro/BitOperationMacros.h"

namespace MEngine
{

namespace RHI
{

enum class ERHIPipelineState : uint8
{
  None = 0,
  Graphics = BIT_FLAG(0),
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_PIPELINE_