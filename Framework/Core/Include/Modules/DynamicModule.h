#pragma once

#ifndef _ME_CORE_DYNAMICMODULE_
#define _ME_CORE_DYNAMICMODULE_

namespace MEngine
{

namespace Module
{

  class IDynamicModule
  {
    public:
      virtual ~IDynamicModule() = default;

      virtual void LoadModule() {}

      virtual void OnPostModuleLoaded() {}

      virtual void OnPreModuleUnloaded() {}

      virtual void UnloadModule() {}

  };

} // namespace MEngine::Module

} // namespace MEngine


#endif // _ME_CORE_DYNAMICMODULE_
