#include "Resources/RHIShaders.h"

namespace MEngine
{

namespace RHI
{

MRHIShader::MRHIShader(IN MEngine::RHI::EResourceType Type, IN MEngine::RHI::EShaderStage Stage)
  : MRHIResource{Type}
  , m_stage{Stage}
{ }

MRHIShader::~MRHIShader() = default;

} // namespace MEngine::RHI

} // namespace MEngine