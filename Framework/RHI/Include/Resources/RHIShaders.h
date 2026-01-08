#pragma once

#ifndef _ME_RHI_SHADERS_
#define _ME_RHI_SHADERS_

#include "Resources/RHIResource.h"

namespace MEngine
{

namespace RHI
{

class MRHIShader : public MRHIResource
{
  public:
    RHI_API MRHIShader(IN MEngine::RHI::EResourceType Type, IN MEngine::RHI::EShaderStage Stage);
    RHI_API virtual ~MRHIShader();

    MEngine::RHI::EShaderStage GetStage() const { return m_stage; }

  private:
    EShaderStage m_stage;
};

class MRHIVertexShader : public MRHIShader
{
  public: 
    MRHIVertexShader()
      : MRHIShader{EResourceType::VertexShader, EShaderStage::Vertex}
    {}
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_SHADERS_