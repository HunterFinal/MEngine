#pragma once

#ifndef _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_
#define _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_

#include "Config/ECSConfig.h"

namespace MEngine
{

namespace ECSCore
{

struct MDefaultEntityPolicy
{
  using ID_Type = uint32;
  inline static constexpr ID_Type ID_Mask = 0xFFFFFFFF;
  inline static constexpr ID_Type ID_Invalid = 0;
};

struct MEntityPolicy_U64
{
  using ID_Type = uint64;
  inline static constexpr ID_Type ID_Mask = 0xFFFFFFFFFFFFFFFF;
  inline static constexpr ID_Type ID_Invalid = 0;
};

} // namespace MEngine::ECSCore

} // namespace MEngine

#endif // _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYPOLICY_