#include "Resources/RHIVertexInputLayout.h"

namespace MEngine
{

namespace RHI
{

bool operator==(IN const MRHIVertexElement& Lhs, IN const MRHIVertexElement& Rhs)
{
  return (Lhs.Offset    == Rhs.Offset)    &&
         (Lhs.Format    == Rhs.Format)    &&
         (Lhs.SlotIndex == Rhs.SlotIndex) &&
         (Lhs.Location  == Rhs.Location)  ;
}

bool operator!=(IN const MRHIVertexElement& Lhs, IN const MRHIVertexElement& Rhs)
{
  return !(Lhs == Rhs);
}

} // namespace MEngine::RHI

} // namespace MEngine