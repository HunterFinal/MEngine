#pragma once

#ifndef _ME_OPENGLDRV_PIPELINESTATE_
#define _ME_OPENGLDRV_PIPELINESTATE_

#include "Resources/RHIPipelineState.h"
#include "Resources/RHIDescriptors.h"

#include "OpenGLShaders.h"
#include "OpenGLVertexInputLayout.h"

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLGraphicsPipelineState : public MEngine::RHI::MRHIGraphicsPipelineState
{

public: 
  MOpenGLGraphicsPipelineState(IN const MEngine::RHI::MRHIGraphicsPipelineStateDescriptor& PSODesc);

  MEngine::RHI::MRHIGraphicsPipelineStateDescriptor PSODescriptor;
  const GLenum                                      GLPrimitiveType;

};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine

#endif // _ME_OPENGLDRV_PIPELINESTATE_