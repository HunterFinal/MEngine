#pragma once

#ifndef _ME_RUNTIME_INPUTCORE_INPUTCOREMODULE_
#define _ME_RUNTIME_INPUTCORE_INPUTCOREMODULE_

#include "Modules/DynamicModule.h"

namespace MEngine
{

namespace InputCore
{

class MInputCoreDynamicModule : public MEngine::Core::IDynamicModule
{
  public:

    /**Start MEngine::Core::IDynamicModule interface */
    void LoadModule() override final;

    void UnloadModule() override final;
    /**End MEngine::Core::IDynamicModule interface */

};

} // namespace MEngine::InputCore

} // namespace MEngine

#endif // _ME_RUNTIME_INPUTCORE_INPUTCOREMODULE_