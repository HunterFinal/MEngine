#pragma once

#ifndef _ME_CORE_MODULES_DYNAMICMODULEMANAGER_
#define _ME_CORE_MODULES_DYNAMICMODULEMANAGER_

#include "CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Modules/DynamicModule.h"

#include <atomic>
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>

namespace MEngine
{

namespace Module
{

  /**
   * @brief Manager
   * 
   */
  class MDynamicModuleManager final
  {
    public:
      CORE_API ~MDynamicModuleManager();

      /**
       * Get the singleton instance of module manager
       */
      static CORE_API MDynamicModuleManager& Get();

    private:

      /**
       * Information of a module
       */
      struct DynamicModuleEntry
      {
        // Module file name(.dll/.so file name)
        std::string Filename;

        // Handle of a module(.dll/.so)
        void* Handle;

        // Module instance of this module. Entry actually owns the module
        std::unique_ptr<IDynamicModule> Module;

        // True if module is full loaded
        std::atomic<bool> bIsLoaded;

        DynamicModuleEntry()
          : Filename{}
          , Handle{nullptr}
          , Module{nullptr}
          , bIsLoaded{false}
        {
        }

        ~DynamicModuleEntry() = default;

        DynamicModuleEntry(const DynamicModuleEntry& Other) = delete;
        DynamicModuleEntry& operator=(const DynamicModuleEntry& Other) = delete;
      };

    public:
      TYPEDEF(DynamicModuleEntry, ModuleEntry);
      TYPEDEF(std::shared_ptr<ModuleEntry>, SharedModuleEntryPtr);

      // Key of ModuleTable
      TYPEDEF(std::string, ModuleKey);
      
      // Value of ModuleTable
      TYPEDEF(SharedModuleEntryPtr, ModuleValue);

      // Actual type of ModuleTable
      #define COMMA ,
      TYPEDEF(std::unordered_map<ModuleKey COMMA ModuleValue>, ModuleTable);
      #undef COMMA

    private:
      // Invalid value of value type in ModuleTable
      static const ModuleValue InvalidEntry;

    public:
      /**
       * Load the specific module
       * 
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return Loaded module.Return nullptr if load failed
       */
      CORE_API IDynamicModule* LoadModule(IN std::string_view ModuleName);

      CORE_API IDynamicModule* GetModule(IN std::string_view ModuleName) const;

      /**
       * Load the specific module with assertion check(Program pause(Only Debug) if not exists)
       * 
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return Loaded module.
       */
      CORE_API IDynamicModule& LoadModuleChecked(IN std::string_view ModuleName);

      template<IMPLEMENTATION_TYPE_CONCEPT<IDynamicModule> TDynamicModule>
      static TDynamicModule* LoadModule(IN std::string_view ModuleName);

      template<IMPLEMENTATION_TYPE_CONCEPT<IDynamicModule> TDynamicModule>
      static TDynamicModule& LoadModuleChecked(IN std::string_view ModuleName);

      CORE_API void UnloadModules(IN bool bIsShutdown);

      CORE_API std::string GetModuleFilename(IN std::string_view ModuleName) const;
      CORE_API bool IsModuleFullLoaded(IN std::string_view ModuleName) const;

    private:
      SharedModuleEntryPtr CreateModule(IN std::string_view ModuleName);

      IDynamicModule* GetOrLoadModule(IN std::string_view ModuleName);

      ModuleValue& GetModuleEntry(IN const std::string& ModuleName) &;
      const ModuleValue& GetModuleEntry(IN const std::string& ModuleName) const&; 

      void SetModuleFilename(IN const std::string& Filename, OUT DynamicModuleEntry& OutModuleEntry);

      ModuleValue FindModule(IN std::string_view ModuleName) const;

      void* LoadModuleInternal(IN std::string_view ModuleFilePath);

      void UnloadModuleInternal(IN std::string_view ModuleName, void* ModuleHandle);

    private:
      ModuleTable m_modules;
  };

  template<IMPLEMENTATION_TYPE_CONCEPT<IDynamicModule> TDynamicModule>
  static TDynamicModule* MDynamicModuleManager::LoadModule(IN std::string_view ModuleName)
  {
    return static_cast<TDynamicModule*>(MDynamicModuleManager::Get().LoadModule(ModuleName));
  }

  template<IMPLEMENTATION_TYPE_CONCEPT<IDynamicModule> TDynamicModule>
  static TDynamicModule& MDynamicModuleManager::LoadModuleChecked(IN std::string_view ModuleName)
  {
    return static_cast<TDynamicModule&>(MDynamicModuleManager::Get().LoadModuleChecked(ModuleName));
  }

} // namespace MEngine::Module

} // namespace MEngine



#endif // _ME_CORE_MODULES_DYNAMICMODULEMANAGER_