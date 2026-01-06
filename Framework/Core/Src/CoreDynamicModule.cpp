#include "CoreDynamicModule.h"

#include <iostream>

MENGINE_IMPLEMENT_DYNAMIC_MODULE(MEngine::Core::MCoreDynamiceModule, Core);

namespace MEngine
{

namespace Core
{
  void MCoreDynamiceModule::Hoge()
  {
    std::wcout << L"Core Dynamic Module HogeHoge!!!" << std::endl;
  }

} // namespace MEngine::Core

} // namespace MEngine
