#pragma once

#ifndef _ME_RHI_BUFFERDESCRIPTOR_
#define _ME_RHI_BUFFERDESCRIPTOR_

#include "CoreDefines.h"
#include "Templates/TypeCast.h"
#include "Macro/AssertionMacros.h"
#include "RHIDefines.h"
#include "RHITypes.h"
#include "RHIFwd.h"

#include "Resources/RHIShaders.h"
#include "Resources/RHIVertexInputLayout.h"

// TODO
#include <memory>

namespace MEngine
{

namespace RHI
{

struct MRHIBufferDescriptor
{
  uint32 BufferSize;

  uint32 ElementStride;

  EBufferUsageType BufferUsage = EBufferUsageType::None;

  const void* BufferInitData;

  RHI_API static const MRHIBufferDescriptor NullDesc;

  RHI_API friend bool operator==(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs);
  RHI_API friend bool operator!=(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs);

  constexpr MRHIBufferDescriptor()
    : BufferSize{0}
    , ElementStride{0}
    , BufferUsage{EBufferUsageType::None}
    , BufferInitData{nullptr}
  { }

  constexpr MRHIBufferDescriptor(IN uint32 Size, IN uint32 Stride, IN EBufferUsageType Usage, IN const void* Data)
    : BufferSize{Size}
    , ElementStride{Stride}
    , BufferUsage{Usage}
    , BufferInitData{Data}
  { }

  MRHIBufferDescriptor(const MRHIBufferDescriptor& Other)
    : BufferSize{Other.BufferSize}
    , ElementStride{Other.ElementStride}
    , BufferUsage{Other.BufferUsage}
    , BufferInitData{Other.BufferInitData}
  {}

  MRHIBufferDescriptor& operator=(const MRHIBufferDescriptor& Other)
  {
    BufferSize     = Other.BufferSize;
    ElementStride  = Other.ElementStride;
    BufferUsage    = Other.BufferUsage;
    BufferInitData = Other.BufferInitData;

    return *this;
  }

  static MRHIBufferDescriptor Null()
  {
    return NullDesc;
  }

  bool IsNull() const
  {
    if ((::EnumCast(BufferUsage) & ::EnumCast(EBufferUsageType::None)) != 0)
    {
      me_assert((BufferSize == 0) && (ElementStride == 0) && (BufferUsage == EBufferUsageType::None));
      return true;
    }

    return false;
  }

};

struct MRHIVertexBinding
{
  uint32 Stride;
  MEngine::RHI::ERHIVertexInputRate InputRate;

  constexpr MRHIVertexBinding()
    : Stride{0}
    , InputRate{MEngine::RHI::ERHIVertexInputRate::PerVertex}
  {}

  RHI_API friend bool operator==(IN const MRHIVertexBinding& Lhs, IN const MRHIVertexBinding& Rhs);
  RHI_API friend bool operator!=(IN const MRHIVertexBinding& Lhs, IN const MRHIVertexBinding& Rhs);

};



struct MRHIVertexBindingDescriptor
{
  MRHIVertexBinding Bindings[MEngine::RHI::MaxVertexBindingCount];
  uint8 BindingValidFlags;
  
  MRHIVertexBindingDescriptor() = default;
  MRHIVertexBindingDescriptor(IN const uint8 InFlags, IN const MRHIVertexBinding* InBindings)
    : Bindings{}
    , BindingValidFlags{InFlags}
  {
    static_assert(sizeof(InFlags) <= sizeof(BindingValidFlags), "InFlags has no enough bits to construct MRHIVertexBindingDescriptor.");
    
    // TODO Not to use memcpy here
    ::memcpy(Bindings, InBindings, sizeof(Bindings));
  }
  
  bool IsBindingValid(IN const uint32 BindingIndex) const
  {
    return ((BindingValidFlags >> BindingIndex) & 1) != 0;
  }
  
  bool IsNull() const
  {
    return BindingValidFlags == 0;
  }
  
};
static_assert(sizeof(MRHIVertexBindingDescriptor::BindingValidFlags) * 8 >= MEngine::RHI::MaxVertexBindingCount, "BindingValidFlags will not able to mark all bits of Bindings. struct MRHIVertexBindingDescriptor");

struct MRHIGraphicsPipelineStateDescriptor
{
  RHIVertexInputLayoutRefPtr RHIInputLayout;
  RHIVertexShaderRefPtr      RHIVertexShader;
  RHIPixelShaderRefPtr       RHIPixelShader;

  EPrimitiveTopologyType     PrimitiveType;
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_BUFFERDESCRIPTOR_