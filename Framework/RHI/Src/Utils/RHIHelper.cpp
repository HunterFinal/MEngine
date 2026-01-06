#include "Utils/RHIHelper.h"
#include "Templates/TypeCast.h"

namespace MEngine
{

namespace RHI
{

uint32 MRHIHelper::GetVertexCountOfPrimitiveType(IN uint32 PrimitiveNum, IN MEngine::RHI::EPrimitiveTopologyType PrimitiveType)
{
  static_assert(::EnumCast(MEngine::RHI::EPrimitiveTopologyType::Num) == 1, "Update this function.");
  uint32 factor{1};
  uint32 offset{0};

  using enum MEngine::RHI::EPrimitiveTopologyType;
  // Get factor
  switch (PrimitiveType)
  {
    case TriangleList: {factor = 3; offset = 0;} break;
  }

  return PrimitiveNum * factor + offset;
}

}

}