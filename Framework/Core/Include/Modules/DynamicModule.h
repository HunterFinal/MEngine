#pragma once

#ifndef _ME_CORE_MODULES_DYNAMICMODULE_
#define _ME_CORE_MODULES_DYNAMICMODULE_

#include "CoreDefines.h"

#include <string>

#ifndef PREDEFINED_MODULE_NAME
  #define PREDEFINED_MODULE_NAME nullptr
#endif

class MDynamicModuleStaticFactoryCenter;

namespace MEngine
{

namespace Core
{
  class IDynamicModule
  {
    public:
      virtual ~IDynamicModule() = default;

      virtual void LoadModule() {}

      virtual void UnloadModule() {}

  };

  typedef IDynamicModule* (*DynamicModuleFactoryPtr)();

  class MDynamicModuleInitializer final
  {
    public:
      CORE_API MDynamicModuleInitializer(IN const std::string& InUserDefinedModuleName, IN DynamicModuleFactoryPtr FactoryPtr, IN const char* InMacroPredefinedName = nullptr);
      CORE_API ~MDynamicModuleInitializer();
      CORE_API bool HasName(IN const std::string& InModuleName) const;

    private:
      const std::string mc_userDefinedName;
      const char* m_macroPredefinedName;
  };

  class IDynamicModuleStaticFactoryCenter
  {
    friend class ::MDynamicModuleStaticFactoryCenter;

    public:
      static CORE_API IDynamicModuleStaticFactoryCenter& Get();
      
      virtual ~IDynamicModuleStaticFactoryCenter() = default;
      virtual DynamicModuleFactoryPtr FindModuleFactory(IN const std::string& ModuleName) = 0;

    private:
      IDynamicModuleStaticFactoryCenter() = default;
  };
} // namespace MEngine::Module

} // namespace MEngine


#define MENGINE_IMPLEMENT_DYNAMIC_MODULE(DynamicModuleImplClassName, ModuleName) \
  static MEngine::Core::IDynamicModule* Create##ModuleName##DynamicModule() \
  { \
    return new DynamicModuleImplClassName(); \
  } \
  static MEngine::Core::MDynamicModuleInitializer s_##ModuleName##Initializer(#ModuleName, Create##ModuleName##DynamicModule, PREDEFINED_MODULE_NAME); 

#endif // _ME_CORE_MODULES_DYNAMICMODULE_
