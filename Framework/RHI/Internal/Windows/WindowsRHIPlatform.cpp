#include "RHIGlobals.h"

#include "Modules/DynamicModuleManager.h"
#include "RHIModule.h"
#include "RHIBackend.h"

namespace RHIGlobals
{
  MEngine::RHI::IRHIBackend* CreateGlobalRHIBackend()
  {
    MEngine::RHI::IRHIModule* RHIModule = MEngine::Core::MDynamicModuleManager::Get().LoadModule<MEngine::RHI::IRHIModule>("OpenGLDriver");

    if (RHIModule != nullptr)
    {
      return RHIModule->CreateRHIBackend();
    }
    
    return nullptr;
  }

  void ShutdownGlobalRHIBackend(IN MEngine::RHI::IRHIBackend* RHIBackend)
  {
    // FIXME Temporary code
    delete RHIBackend;
  }
} // namespace RHIGlobals
