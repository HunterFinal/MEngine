#include "InputCoreModule.h"

MENGINE_IMPLEMENT_DYNAMIC_MODULE(MEngine::InputCore::MInputCoreDynamicModule, InputCore);

extern void InitializeInputCore();
extern void DeinitializeInputCore();

namespace MEngine
{

namespace InputCore
{

void MInputCoreDynamicModule::LoadModule()
{
  InitializeInputCore();
}

void MInputCoreDynamicModule::UnloadModule()
{
  DeinitializeInputCore();
}

} // namespace MEngine::InputCore

} // namespace MEngine