#pragma once

#ifndef _ME_RHI_PIPELINESTATE_
#define _ME_RHI_PIPELINESTATE_

#include "Resources/RHIResource.h"

namespace MEngine
{

namespace RHI
{

class MRHIGraphicsPipelineState : public MEngine::RHI::MRHIResource
{

public:
  MRHIGraphicsPipelineState()
    : MRHIResource{MEngine::RHI::EResourceType::GraphicsPSO}
  { }

};

} // namespace MEngine::RHI 

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIGraphicsPipelineState>, RHIGraphicsPipelineStateRefPtr);

#endif // _ME_RHI_PIPELINESTATE_