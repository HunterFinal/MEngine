#pragma once

#ifndef _ME_CORE_MODULES_DYNAMICMODULEMANAGER_
#define _ME_CORE_MODULES_DYNAMICMODULEMANAGER_

#include "CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Modules/DynamicModule.h"

#include <atomic>
#include <string>
#include <string_view>
#include <map>
#include <unordered_map>
#include <memory>

namespace MEngine
{

namespace Core
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
        std::wstring Filename;

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

      /**
       * Load the specific module with specific type
       * 
       * @tparam TDynamicModule Derived class of IDynamicModule
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return Loaded module.Return nullptr if load failed
       */
#if !HAS_CPP_20
      template<typename TDynamicModule>
#else
      template<std::derived_from<MEngine::Core::IDynamicModule> TDynamicModule>
#endif
      static TDynamicModule* LoadModule(IN std::string_view ModuleName);

      /**
       * Load the specific module with specific type.Assertion check(Program pause(Only Debug) if not exists)
       * 
       * @tparam TDynamicModule Derived class of IDynamicModule
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return Loaded module.
       */
#if !HAS_CPP_20
      template<typename TDynamicModule>
#else
      template<std::derived_from<MEngine::Core::IDynamicModule> TDynamicModule>
#endif
      static TDynamicModule& LoadModuleChecked(IN std::string_view ModuleName);

      /**
       * @brief Unload modules.We will add order to module for dependency purpose so we can reference dependency module safely during unloading
       * 
       * @param bIsShutdown If true, we are exiting an application.
       */
      CORE_API void UnloadModules(IN bool bIsShutdown);

      /**
       * @brief Checks whether the specified module is fully loaded
       * 
       * O(1) operation
       * 
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return true if module is fully loaded, false otherwise
       */
      CORE_API bool IsModuleFullLoaded(IN std::string_view ModuleName) const;

    private:
      
      /**
       * @brief Creates a module and adds to our table of modules.Will not create one if given name of module is exists
       * 
       * @param ModuleName Base name of module file.(without file path/extension suffix)
       * @return New module entry we created, InvalidEntry if exists
       */
      SharedModuleEntryPtr CreateModule(IN std::string_view ModuleName);

      ModuleValue FindModule(IN std::string_view ModuleName) const;
      IDynamicModule* GetOrLoadModule(IN std::string_view ModuleName);
      void* LoadLibraryInternal(IN std::wstring_view ModuleFilePath);
      void UnloadLibraryInternal(IN std::string_view ModuleName, IN const bool bIsShutdown);

      void FindModulePathFromManifest(IN const std::string& ModuleName, OUT std::wstring& OutModuleFilePath);
      void SetupModuleFilenameFromManifest(IN std::string_view ModuleName, OUT ModuleEntry& OutModuleEntry);

    private:
      /**Table of all modules */
      ModuleTable m_modules;

      /**Map of all known module paths(Caching use). To prevent frequent manifest file read operation */
      std::map<std::string, std::wstring> m_modulePathsCache;
  };


#if !HAS_CPP_20
      template<typename TDynamicModule>
#else
      template<std::derived_from<MEngine::Core::IDynamicModule> TDynamicModule>
#endif
  TDynamicModule* MDynamicModuleManager::LoadModule(IN std::string_view ModuleName)
  {
#if !HAS_CPP_20
    static_assert(std::is_base_of<MEngine::Core::IDynamicModule, TDynamicModule>::value, "Type of LoadModule should be a derived class of IDynamicModule.");
#endif
    return static_cast<TDynamicModule*>(MDynamicModuleManager::Get().LoadModule(ModuleName));
  }

#if !HAS_CPP_20
      template<typename TDynamicModule>
#else
      template<std::derived_from<MEngine::Core::IDynamicModule> TDynamicModule>
#endif
  TDynamicModule& MDynamicModuleManager::LoadModuleChecked(IN std::string_view ModuleName)
  {
#if !HAS_CPP_20
    static_assert(std::is_base_of<MEngine::Core::IDynamicModule, TDynamicModule>::value, "Type of LoadModule should be a derived class of IDynamicModule.");
#endif
    return static_cast<TDynamicModule&>(MDynamicModuleManager::Get().LoadModuleChecked(ModuleName));
  }

} // namespace MEngine::Module

} // namespace MEngine



#endif // _ME_CORE_MODULES_DYNAMICMODULEMANAGER_