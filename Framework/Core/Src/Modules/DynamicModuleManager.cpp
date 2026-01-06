#include "Modules/DynamicModuleManager.h"

#include "Modules/DynamicModuleManifest.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformStringUtility.h"
#include "Macro/AssertionMacros.h"
#include <vector>

namespace MEngine
{

namespace Core
{

const MDynamicModuleManager::ModuleValue MDynamicModuleManager::InvalidEntry = nullptr;

MDynamicModuleManager::~MDynamicModuleManager() = default;

MDynamicModuleManager& MDynamicModuleManager::Get()
{
  static MDynamicModuleManager sInstance{};
  return sInstance;
}

IDynamicModule* MDynamicModuleManager::GetModule(IN std::string_view ModuleName) const
{
  ModuleKey moduleKeyToFind{ModuleName};
  ModuleTable::const_iterator moduleItr = m_modules.find(moduleKeyToFind);
  if (moduleItr == m_modules.cend())
  {
    return nullptr;
  }

  const ModuleValue& foundModuleEntry = moduleItr->second;
  if (foundModuleEntry->bIsLoaded && foundModuleEntry->Module != nullptr)
  {
    return foundModuleEntry->Module.get();
  }

  // TODO Need output error log
  return nullptr;
}

IDynamicModule* MDynamicModuleManager::LoadModule(IN std::string_view ModuleName)
{
  return GetOrLoadModule(ModuleName);
}

IDynamicModule& MDynamicModuleManager::LoadModuleChecked(IN std::string_view ModuleName)
{
  IDynamicModule* loadedModule = GetOrLoadModule(ModuleName);

  me_assert(loadedModule != nullptr);
  return *loadedModule;
}

void MDynamicModuleManager::UnloadModules(IN bool bIsShutdown)
{
  struct UnloadDynamicModuleEntry
  {
    std::string ModuleName;
    IDynamicModule* Module;

    UnloadDynamicModuleEntry(IN const std::string& InModuleName, IN IDynamicModule* InModule)
      : ModuleName{InModuleName}
      , Module{InModule}
    {}
  };

  std::vector<UnloadDynamicModuleEntry> modulesToUnload{};
  modulesToUnload.reserve(m_modules.size());

  for (const auto& moduleEntry : m_modules)
  {
    // Unload loaded module
    if (moduleEntry.second->Module != nullptr)
    {
      modulesToUnload.emplace_back(moduleEntry.first, moduleEntry.second->Module.get());
    }
  }

  for (UnloadDynamicModuleEntry& moduleToUnload : modulesToUnload)
  {
    UnloadLibraryInternal(moduleToUnload.ModuleName, bIsShutdown);
    moduleToUnload.Module = nullptr;
  }
}

bool MDynamicModuleManager::IsModuleFullLoaded(IN std::string_view ModuleName) const
{
  SharedModuleEntryPtr moduleEntry = FindModule(ModuleName);

  return (moduleEntry != nullptr) ? (moduleEntry->Module != nullptr) : false;
}

MDynamicModuleManager::SharedModuleEntryPtr MDynamicModuleManager::CreateModule(IN std::string_view ModuleName)
{
  std::string moduleNameKey{ModuleName};

  if (!m_modules.contains(moduleNameKey))
  { 
    auto moduleEntryFactory = []()
    {
      return std::make_shared<DynamicModuleEntry>();
    };
  
    SharedModuleEntryPtr newEntry = moduleEntryFactory();
    me_assert(newEntry != InvalidEntry);
  
    SetupModuleFilenameFromManifest(moduleNameKey, *newEntry);
  
    // Add new entry to table
    m_modules.emplace(moduleNameKey, newEntry);
  }

  return m_modules[moduleNameKey];
}

IDynamicModule* MDynamicModuleManager::GetOrLoadModule(IN std::string_view ModuleName)
{
  // Get loaded module
  IDynamicModule* modulePtr = GetModule(ModuleName);
  if (modulePtr != nullptr)
  {
    return modulePtr;
  }

  // Load module into memory
  // Create new module entry
  SharedModuleEntryPtr newModuleEntry = CreateModule(ModuleName);

  // Load dll/so if it is not linked to program
  {
    std::wstring libraryFilePathToLoad{};
    std::string moduleNameStr = std::string{ModuleName};
    
    FindModulePathFromManifest(moduleNameStr, libraryFilePathToLoad);

    newModuleEntry->Handle = nullptr;

    // Load library 
    if (true)
    {
      newModuleEntry->Handle = LoadLibraryInternal(libraryFilePathToLoad);

      // Load success. Next we load dynamic module
      if (newModuleEntry->Handle != nullptr)
      {
        DynamicModuleFactoryPtr factoryPtr = IDynamicModuleStaticFactoryCenter::Get().FindModuleFactory(moduleNameStr);

        if (factoryPtr != nullptr)
        {
          if (newModuleEntry->Module != nullptr)
          {
            // Assign already loaded dynamic module
            modulePtr = newModuleEntry->Module.get();
          }
          // Initialize the module
          else
          {
            newModuleEntry->Module = std::unique_ptr<IDynamicModule>(factoryPtr());

            if (newModuleEntry->Module != nullptr)
            {
              // Load the module
              newModuleEntry->Module->LoadModule();

              // Now the module is fully loaded.It can be used in another thread.
              newModuleEntry->bIsLoaded = true;
  
              modulePtr = newModuleEntry->Module.get();
            }
            // Since we can not get a valid dynamice module here, so we decide to release the library 
            else
            {
              UnloadLibraryInternal(ModuleName, false);
            }

          }
        }
        // We can not create a dynamice module. Release the library
        else
        {
          UnloadLibraryInternal(ModuleName, false);
        }
      }
    }
  }

  return modulePtr;
}

MDynamicModuleManager::ModuleValue MDynamicModuleManager::FindModule(IN std::string_view ModuleName) const
{
  const std::string moduleNameStr{ModuleName};

  ModuleTable::const_iterator foundEntryItr{};
  foundEntryItr = m_modules.find(moduleNameStr);
  if (foundEntryItr != m_modules.cend())
  {
    return foundEntryItr->second;
  }

  return InvalidEntry;
}

void* MDynamicModuleManager::LoadLibraryInternal(IN std::wstring_view ModuleFilePath)
{
  void* loadedHandle = nullptr;

  loadedHandle = MPlatformLowLevelAccessPort::GetDllLibrary(ModuleFilePath.data());

  return loadedHandle;
}

void MDynamicModuleManager::UnloadLibraryInternal(IN std::string_view ModuleName, IN const bool bIsShutdown)
{
  // Find exists module
  SharedModuleEntryPtr moduleEntryPtr = FindModule(ModuleName);

  if (moduleEntryPtr != nullptr)
  {
    DynamicModuleEntry& moduleEntry = *moduleEntryPtr;

    if (moduleEntry.Module != nullptr)
    {
      moduleEntry.bIsLoaded = false;

      // Actual unload the module
      moduleEntry.Module->UnloadModule();

      moduleEntry.Module.reset();
    }

    // Unload .dll/.so
    if (moduleEntry.Handle != nullptr)
    {
      if (!bIsShutdown)
      {
        MPlatformLowLevelAccessPort::UnloadDllLibrary(moduleEntry.Handle);
        moduleEntry.Handle = nullptr;
      }
    }
  }
}

void MDynamicModuleManager::FindModulePathFromManifest(IN const std::string& ModuleName, OUT std::wstring& OutModuleFilePath)
{
  const std::wstring baseDir = MPlatformLowLevelAccessPort::GetBaseDir();
  // Cache the manifest
  if (m_modulePathsCache.size() == 0)
  {
    std::wstring manifestPath = MModuleManifest::GetFilename(baseDir);

    MModuleManifest manifest{};
    const bool bLoadSuccess = MModuleManifest::ReadManifest(manifestPath, manifest);
    if (bLoadSuccess)
    {
      // Read the loaded module path 
      for (const auto& [ModuleNameWide, ModuleRelativePathWide] : manifest.ModuleNameFilenameTable)
      {
        std::string moduleNameAsKey{};
        const SIZE_T convertLength = ModuleNameWide.size();
        moduleNameAsKey.resize(convertLength);

        // Convert wstring to string(wchar_t to char.)
        // NOTE:May lost character
        (void)MPlatformStringUtility::ConvertToDest(moduleNameAsKey.data(), convertLength, ModuleNameWide.data(), convertLength);
        
        // TODO
        const std::wstring combinedModulePath = (baseDir + ModuleRelativePathWide);
        m_modulePathsCache.emplace(moduleNameAsKey, combinedModulePath);
      }
    }
  }

  decltype(m_modulePathsCache)::iterator foundPath = m_modulePathsCache.find(ModuleName);
  if (foundPath != m_modulePathsCache.end())
  {
    OutModuleFilePath = foundPath->second;
  }
}

void MDynamicModuleManager::SetupModuleFilenameFromManifest(IN std::string_view ModuleName, OUT ModuleEntry& OutModuleEntry)
{
  const std::string moduleNameKey{ModuleName};

  std::wstring moduleFilename;
  FindModulePathFromManifest(moduleNameKey, moduleFilename);

  // TODO
  if (moduleFilename.size() == 0)
  {
    return;
  }

  OutModuleEntry.Filename = moduleFilename;
}

} // namespace MEngine::Core
} // namespace MEngine