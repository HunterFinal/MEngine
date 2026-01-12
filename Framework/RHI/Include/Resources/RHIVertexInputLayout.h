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
  uint32 Offset;
  MEngine::RHI::ERHIVertexFormat Format;
  uint8 SlotIndex;
  uint8 Location;

  MRHIVertexElement()
    : Offset{0}
    , Format{MEngine::RHI::ERHIVertexFormat::None}
    , SlotIndex{0}
    , Location{0}
  {}

  MRHIVertexElement(IN uint32 InOffset, IN MEngine::RHI::ERHIVertexFormat InFormat, IN uint8 InSlotIndex, IN uint8 InLocation)
    : Offset{InOffset}
    , Format{InFormat}
    , SlotIndex{InSlotIndex}
    , Location{InLocation}
  {}

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