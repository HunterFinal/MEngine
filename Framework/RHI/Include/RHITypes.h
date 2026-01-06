#pragma once

#ifndef _ME_RHI_TYPES_
#define _ME_RHI_TYPES_

#include "CoreDefines.h"
#include "Templates/TypeCast.h"
#include "Macro/BitOperationMacros.h"

namespace MEngine
{

namespace RHI
{

enum class EResourceType : uint8
{
  None,

  Buffer,
  VertexShader,
  PixelShader,

  MaxNum,
};

enum class EPrimitiveTopologyType : uint8
{
  // PointList,
  // LineList,
  // LineListAdjacency,
  // LineStrip,
  // LineStripAdjacency,
  TriangleList,
  // TriangleListAdjacency,
  // TriangleStrip,
  // TriangleStripAdjacency,

  Num,
};
static_assert(::EnumCast(EPrimitiveTopologyType::Num) <= (1 << 8), "EPrimitiveTopologyType does not fit in a byte");

// FIXME This currently only support OpenGL
enum class EBufferUsageType : uint32
{
  None = 0,

  /**The buffer data is set only once and used many times. */
  Static = BIT_FLAG(0),

  /**The buffer data is changed a lot and used many times */
  Dynamic = BIT_FLAG(1),

};

enum class EResourceAccessMode : uint8
{
  ReadOnly,
  WriteOnly,
};

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_TYPES_