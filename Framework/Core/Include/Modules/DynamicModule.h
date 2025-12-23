#pragma once

#ifndef _ME_CORE_MODULES_DYNAMICMODULE_
#define _ME_CORE_MODULES_DYNAMICMODULE_

namespace MEngine
{

namespace Module
{

  class IDynamicModule
  {
    public:
      virtual ~IDynamicModule() = default;

      virtual void LoadModule() {}

      virtual void UnloadModule() {}

  };

} // namespace MEngine::Module

} // namespace MEngine


#endif // _ME_CORE_MODULES_DYNAMICMODULE_
