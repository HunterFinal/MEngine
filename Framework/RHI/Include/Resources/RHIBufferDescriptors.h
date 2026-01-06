#pragma once

#ifndef _ME_RHI_BUFFERDESCRIPTOR_
#define _ME_RHI_BUFFERDESCRIPTOR_

#include "CoreDefines.h"
#include "Templates/TypeCast.h"
#include "Macro/AssertionMacros.h"
#include "RHIDefines.h"
#include "RHITypes.h"

namespace MEngine
{

namespace RHI
{

enum class EBufferUsageType : uint32;

struct MRHIBufferDescriptor
{
  uint32 BufferSize;

  uint32 ElementStride;

  EBufferUsageType BufferUsage = EBufferUsageType::None;

  RHI_API static const MRHIBufferDescriptor NullDesc;

  RHI_API friend bool operator==(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs);
  RHI_API friend bool operator!=(const MRHIBufferDescriptor& Lhs, const MRHIBufferDescriptor& Rhs);

  constexpr MRHIBufferDescriptor()
    : BufferSize{0}
    , ElementStride{0}
    , BufferUsage{EBufferUsageType::None}
  { }

  constexpr MRHIBufferDescriptor(IN uint32 Size, IN uint32 Stride, IN EBufferUsageType Usage)
    : BufferSize{Size}
    , ElementStride{Stride}
    , BufferUsage{Usage}
  { }

  MRHIBufferDescriptor(const MRHIBufferDescriptor& Other)
    : BufferSize{Other.BufferSize}
    , ElementStride{Other.ElementStride}
    , BufferUsage{Other.BufferUsage}
  {}

  MRHIBufferDescriptor& operator=(const MRHIBufferDescriptor& Other)
  {
    BufferSize    = Other.BufferSize;
    ElementStride = Other.ElementStride;
    BufferUsage   = Other.BufferUsage;

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

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_BUFFERDESCRIPTOR_