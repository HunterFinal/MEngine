#include "Modules/DynamicModuleManager.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "Macro/AssertionMacros.h"

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

}

void MDynamicModuleManager::UnloadModules(IN bool bIsShutdown)
{

}

std::string MDynamicModuleManager::GetModuleFilename(IN std::string_view ModuleName) const
{

}

bool MDynamicModuleManager::IsModuleFullLoaded(IN std::string_view ModuleName) const
{

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

}

void* MDynamicModuleManager::LoadModuleInternal(IN std::string_view ModuleFilePath)
{

}

void MDynamicModuleManager::UnloadModuleInternal(IN std::string_view ModuleName, void* ModuleHandle)
{

}

} // namespace MEngine::Module

} // namespace MEngine