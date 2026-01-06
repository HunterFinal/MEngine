#include "Resources/RHIBuffers.h"

namespace MEngine
{

namespace RHI
{

MRHIBuffer::MRHIBuffer(const MRHIBufferDescriptor& Descriptor)
  : MRHIResource{MEngine::RHI::EResourceType::Buffer}
  , m_descriptor{Descriptor}
{ }

}
  
}