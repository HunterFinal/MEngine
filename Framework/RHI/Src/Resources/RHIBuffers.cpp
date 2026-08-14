#include "Resources/RHIBuffers.h"

namespace MEngine
{

namespace RHI
{

MRHIBuffer::MRHIBuffer(const MRHIBufferDescriptor& Descriptor)
  : MRHIResource{MEngine::RHI::EResourceType::UniformBuffer}
  , m_descriptor{Descriptor}
{ }

} // namespace MEngine::RHI
  
} // namespace MEngine