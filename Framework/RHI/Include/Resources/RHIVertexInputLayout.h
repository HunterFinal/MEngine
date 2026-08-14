#pragma once

#ifndef _ME_RHI_VERTEXINPUTLAYOUT_
#define _ME_RHI_VERTEXINPUTLAYOUT_

#include "Resources/RHIResource.h"

namespace MEngine
{

namespace RHI
{

struct MRHIVertexElement
{
  const uint32 Offset = 0;
  const MEngine::RHI::ERHIVertexFormat Format = MEngine::RHI::ERHIVertexFormat::None;
  const uint8 Location = 0;
  const uint8 SlotIndex = 0;

  RHI_API friend bool operator==(IN const MRHIVertexElement& Lhs, IN const MRHIVertexElement& Rhs);
  RHI_API friend bool operator!=(IN const MRHIVertexElement& Lhs, IN const MRHIVertexElement& Rhs);
};

class MRHIVertexInputLayout : public MEngine::RHI::MRHIResource
{

public:
  MRHIVertexInputLayout()
    : MEngine::RHI::MRHIResource{MEngine::RHI::EResourceType::VertexInputLayout}
  { }

};

} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIVertexInputLayout>, RHIVertexInputLayoutRefPtr);

#endif // _ME_RHI_VERTEXINPUTLAYOUT_