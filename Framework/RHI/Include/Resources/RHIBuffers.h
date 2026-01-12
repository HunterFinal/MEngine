#pragma once

#ifndef _ME_RHI_BUFFER_
#define _ME_RHI_BUFFER_

#include "Resources/RHIResource.h"
#include "Resources/RHIDescriptors.h"

namespace MEngine
{

namespace RHI
{

class MRHIBuffer : public MRHIResource
{

public:
  RHI_API MRHIBuffer(const MRHIBufferDescriptor& Descriptor);

  const MRHIBufferDescriptor& GetDesc() const { return m_descriptor; }
  uint32 GetSize() const { return m_descriptor.BufferSize; }
  uint32 GetStride() const { return m_descriptor.ElementStride; }
  MEngine::RHI::EBufferUsageType GetUsage() const { return m_descriptor.BufferUsage; }

private:
  const MRHIBufferDescriptor m_descriptor;

};

} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIBuffer>, RHIBufferRefPtr);

#endif // _ME_RHI_BUFFER_

