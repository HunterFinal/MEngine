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
  protected:
    RHI_API MRHIShader(IN MEngine::RHI::EResourceType Type, IN MEngine::RHI::EShaderStage Stage);

  public:
    RHI_API virtual ~MRHIShader();

    MEngine::RHI::EShaderStage GetStage() const { return m_stage; }

  private:
    EShaderStage m_stage;
};

template<EResourceType ResType, EShaderStage StageType>
class TRHIShader : public MRHIShader
{
  public: 
    TRHIShader()
      : MRHIShader{ResType, StageType}
    {}
};

// TODO
using MRHIVertexShader = TRHIShader<EResourceType::VertexShader, EShaderStage::Vertex>;
using MRHIPixelShader = TRHIShader<EResourceType::PixelShader, EShaderStage::Pixel>;

} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIShader>, RHIShaderRefPtr);
TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIVertexShader>, RHIVertexShaderRefPtr);
TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIPixelShader>, RHIPixelShaderRefPtr);


#endif // _ME_RHI_SHADERS_