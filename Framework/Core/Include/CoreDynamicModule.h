#pragma once

#ifndef _ME_CORE_DYNAMIC_MODULE_
#define _ME_CORE_DYNAMIC_MODULE_

#include "CoreDefines.h"
#include "Modules/DynamicModule.h"

namespace MEngine
{

namespace Core
{

class MCoreDynamiceModule : public MEngine::Core::IDynamicModule
{
  public:
    CORE_API void Hoge();
};

} // namespace MEngine::Core

} // namespace MEngine

#endif // _ME_CORE_DYNAMIC_MODULE_