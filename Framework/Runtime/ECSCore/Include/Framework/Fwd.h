#pragma once

#ifndef _ME_RUNTIME_ECSCORE_FRAMEWORK_FWD_
#define _ME_RUNTIME_ECSCORE_FRAMEWORK_FWD_

#include "Config/ECSConfig.h"
#include "EntityPolicy.h"

namespace MEngine
{

namespace ECSCore
{

template<typename EntityPolicyType = MDefaultEntityPolicy>
class MEntity;

} // namespace MEngine::ECSCore

} // namespace MEngine

#endif // _ME_RUNTIME_ECSCORE_FRAMEWORK_FWD_