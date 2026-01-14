#include "OpenGLPipelineState.h"

namespace MEngine
{

namespace OpenGLDrv
{

extern GLenum PrimitiveRHIToGL(IN MEngine::RHI::EPrimitiveTopologyType RHIPrimitiveType);

MOpenGLGraphicsPipelineState::MOpenGLGraphicsPipelineState(IN const MEngine::RHI::MRHIGraphicsPipelineStateDescriptor& PSODesc)
  : PSODescriptor{PSODesc}
  , GLPrimitiveType{PrimitiveRHIToGL(PSODesc.PrimitiveType)}
{
  
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine