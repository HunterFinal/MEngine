#include "Modules/DynamicModule.h"

#include "Macro/AssertionMacros.h"
#include "HAL/PlatformStringUtility.h"
#include <unordered_map>

class MDynamicModuleStaticFactoryCenter final : public MEngine::Core::IDynamicModuleStaticFactoryCenter
{
  public:
    ~MDynamicModuleStaticFactoryCenter() noexcept override = default;

    MEngine::Core::DynamicModuleFactoryPtr FindModuleFactory(IN const std::string& ModuleName) override
    {
      // Use Key->HasName to search exactly dynamic module factory function pointer
      const auto hasNamePred = [&ModuleName](const decltype(m_factories)::value_type& InElementPair)
      {
        return (InElementPair.first != nullptr) && InElementPair.first->HasName(ModuleName);
      };

      decltype(m_factories)::iterator foundItr = std::find_if(m_factories.begin(), m_factories.end(), hasNamePred);
      if (foundItr != m_factories.end())
      {
        return foundItr->second;
      }

      // WARNING: Reach this means module does not exist(Maybe you did not use MENGINE_IMPLEMENT_DYNAMICE_MODULE macro)
      return nullptr;
    }

    void RegisterFactory(IN MEngine::Core::MDynamicModuleInitializer* Initializer, IN MEngine::Core::DynamicModuleFactoryPtr FactoryPtr)
    {
      me_assert((Initializer != nullptr) && (FactoryPtr != nullptr));

      if (!m_factories.contains(Initializer))
      {
        m_factories.emplace(Initializer, FactoryPtr);
      }
    }

    static MDynamicModuleStaticFactoryCenter& Get()
    {
      static MDynamicModuleStaticFactoryCenter sInstance;
      return sInstance;
    }

  private:
    std::unordered_map<MEngine::Core::MDynamicModuleInitializer*, MEngine::Core::DynamicModuleFactoryPtr> m_factories;
};

namespace MEngine
{

namespace Core
{

MDynamicModuleInitializer::MDynamicModuleInitializer(IN const std::string& InUserDefinedModuleName, IN DynamicModuleFactoryPtr FactoryPtr, IN const char* InMacroPredefinedName)
  : mc_userDefinedName{InUserDefinedModuleName}
  , m_macroPredefinedName{nullptr}
{
  // Use both name as signal when two names are different
  if (MPlatformStringUtility::Strcmp(InUserDefinedModuleName.c_str(), InMacroPredefinedName) != 0)
  {
    m_macroPredefinedName = InMacroPredefinedName;
  }

  MDynamicModuleStaticFactoryCenter::Get().RegisterFactory(this, FactoryPtr);
}

MDynamicModuleInitializer::~MDynamicModuleInitializer() = default;

bool MDynamicModuleInitializer::HasName(IN const std::string& InModuleName) const
{
  if (MPlatformStringUtility::Strcmp(mc_userDefinedName.c_str(), InModuleName.c_str()) == 0)
  {
    return true;
  }
  else if ((m_macroPredefinedName != nullptr) && MPlatformStringUtility::Strcmp(m_macroPredefinedName, InModuleName.c_str()) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

IDynamicModuleStaticFactoryCenter& IDynamicModuleStaticFactoryCenter::Get()
{
  return MDynamicModuleStaticFactoryCenter::Get();
}

} // namespace MEngine::Core

} // namespace MEngine