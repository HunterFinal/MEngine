#pragma once

#ifndef _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_
#define _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_

#include "Config/ECSConfig.h"
#include <bit>

namespace MEngine
{

namespace ECSCore
{

struct MDefaultEntityPolicy
{
  using Entity_Type = uint32;
  using ID_Type = uint32;
  using Generation_Type = uint16;
  inline static constexpr ID_Type ID_Mask = 0xFFFFF;
  inline static constexpr Generation_Type Generation_Mask = 0xFFF;
  inline static constexpr Entity_Type Entity_Invalid = (Generation_Mask << std::popcount(ID_Mask)) | ID_Mask;
};

struct MEntityPolicy_U64
{
  using Entity_Type = uint64;
  using ID_Type = uint64;
  using Generation_Type = uint32;
  inline static constexpr ID_Type ID_Mask = 0xFFFFFFFF;
  inline static constexpr Generation_Type Generation_Mask = 0xFFFFFFFF;
  inline static constexpr ID_Type ID_Invalid = ID_Mask;
};

} // namespace MEngine::ECSCore

} // namespace MEngine

#endif // _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_