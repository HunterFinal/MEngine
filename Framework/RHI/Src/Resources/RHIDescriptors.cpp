#include "Resources/RHIDescriptors.h"

namespace MEngine
{

namespace RHI
{

bool operator==(IN const MRHIVertexBinding& Lhs, IN const MRHIVertexBinding& Rhs)
{
  return (Lhs.Stride    == Rhs.Stride)    &&
         (Lhs.InputRate == Rhs.InputRate) ;
}
  
bool operator!=(IN const MRHIVertexBinding& Lhs, IN const MRHIVertexBinding& Rhs)
{
  return !(Lhs == Rhs);
}

const MRHIBufferDescriptor MRHIBufferDescriptor::NullDesc = MRHIBufferDescriptor{0, 0, EBufferUsageType::None, nullptr};

bool operator==(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs)
{
  return (Lhs.BufferSize    == Rhs.BufferSize)    &&
         (Lhs.ElementStride == Rhs.ElementStride) &&
         (Lhs.BufferUsage   == Rhs.BufferUsage)   ;
}

bool operator!=(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs)
{
  return !(Lhs == Rhs);
}

} // namespace MEngine::RHI

} // namespace MEngine