#include "Modules/DynamicModuleManager.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "Macro/AssertionMacros.h"
#include <vector>

namespace MEngine
{

namespace Module
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

std::string MDynamicModuleManager::GetModuleFilename(IN std::string_view ModuleName) const
{
  SharedModuleEntryPtr moduleEntry = FindModule(ModuleName);

  return (moduleEntry != nullptr) ? moduleEntry->Filename : std::string{""};
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
    return InvalidEntry;
  }

  auto moduleEntryFactory = []()
  {
    return std::make_shared<DynamicModuleEntry>();
  };

  SharedModuleEntryPtr newEntry = moduleEntryFactory();
  me_assert(newEntry != InvalidEntry);

  SetModuleFilename(moduleNameKey, *newEntry);

  // Add new entry to table
  m_modules.emplace(moduleNameKey, newEntry);

  return newEntry;
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

  // Loadup Module
  {
    // TODO Add initialization function
    newModuleEntry->Module = nullptr;

    if (newModuleEntry->Module != nullptr)
    {
      // Startup module 
      newModuleEntry->Module->LoadModule();

      newModuleEntry->bIsLoaded = true;

      // Refresh return parameter
      modulePtr = newModuleEntry->Module.get();
    }
  }

  // Load dll/so if it is not linked to program
  {
    newModuleEntry->Handle = nullptr;

    const std::wstring libraryFilePathToLoad{newModuleEntry->Filename};

    // TODO 
    if (true)
    {
      newModuleEntry->Handle = LoadLibraryInternal(libraryFilePathToLoad);
    }
  }

  me_assert( ( (modulePtr != nullptr) && IsModuleFullLoaded(ModuleName) ) );
  return modulePtr;
}

MDynamicModuleManager::ModuleValue& MDynamicModuleManager::GetModuleEntry(IN const std::string& ModuleName) &
{
  const_cast<const MDynamicModuleManager*>(this)->GetModuleEntry(ModuleName);
}
const MDynamicModuleManager::ModuleValue& MDynamicModuleManager::GetModuleEntry(IN const std::string& ModuleName) const&
{
  ModuleTable::const_iterator foundItr = m_modules.find(ModuleName);
  me_assert(foundItr != m_modules.cend());

  return foundItr->second;
}

void MDynamicModuleManager::SetModuleFilename(IN const std::string& Filename, OUT DynamicModuleEntry& OutModuleEntry)
{
  // FIXME Refactoring this function!!!
  OutModuleEntry.Filename = Filename;
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

  loadedHandle = MPlatformLowLevelAccessPort::GetDLLLibrary(ModuleFilePath.data());

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
        MPlatformLowLevelAccessPort::UnloadDLLLibrary(moduleEntry.Handle);
      }
    }
  }
}

} // namespace MEngine::Module

} // namespace MEngine