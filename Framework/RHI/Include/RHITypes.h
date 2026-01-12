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
  GraphicsPSO,
  VertexInputLayout,
  Viewport,

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
  Static       = BIT_FLAG(0),

  /**The buffer data is changed a lot and used many times */
  Dynamic      = BIT_FLAG(1),

  /** */
  VertexBuffer = BIT_FLAG(2),

  IndexBuffer  = BIT_FLAG(3),

};

enum class EResourceAccessMode : uint8
{
  ReadOnly,
  WriteOnly,
};

enum class EShaderStage : uint8
{
  Vertex = 0,
  Pixel,
  Fragment = Pixel,       // Alias

  MaxStageNum,
};

inline constexpr uint64 MAX_STAGE_NUM = static_cast<uint64>(::EnumCast(EShaderStage::MaxStageNum));

enum class ERHIVertexFormat : uint8
{
  None,
  Float2,
  Float3,
};

enum class ERHIVertexInputRate : uint8
{
  PerVertex,
  PerInstance,
};

#if HAS_CPP_17
inline constexpr uint8 MaxVertexBindingCount = 8;
inline constexpr uint8 MaxVertexElementCount = 16;
inline constexpr uint8 MaxVertexBindingCount_BitDigits = 4;
inline constexpr uint8 MaxVertexElementCount_BitDigits = 5;
#else
enum
{
  MaxVertexBindingCount = 8;
  MaxVertexElementCount = 16;
  MaxVertexBufferCount_BitDigits = 4;
  MaxVertexElementCount_BitDigits = 5;
};
#endif
static_assert(MaxVertexBindingCount <= (1 << MaxVertexBindingCount_BitDigits), "MaxVertexBindingCount will not fit on MaxVertexBindingCount_BitDigits");
static_assert(MaxVertexElementCount <= (1 << MaxVertexElementCount_BitDigits), "MaxVertexElementCount will not fit on MaxVertexElementCount_BitDigits");

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_TYPES_