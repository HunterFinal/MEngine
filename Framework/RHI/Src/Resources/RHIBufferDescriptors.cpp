#include "Resources/RHIBufferDescriptors.h"

namespace MEngine
{

namespace RHI
{

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