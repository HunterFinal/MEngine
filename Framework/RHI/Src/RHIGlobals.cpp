#include "RHIGlobals.h"
#include "RHIBackend.h"

MEngine::RHI::IRHIBackend* gRHIBackend = nullptr; 
bool gIsRHIBackendInitialized = false;

namespace MEngine
{

namespace RHI
{

void RHIInitialize()
{
  if (gRHIBackend != nullptr)
  {
    return;
  }

  gRHIBackend = RHIGlobals::CreateGlobalRHIBackend();

  if (gRHIBackend != nullptr)
  {
    gRHIBackend->Initialize();
  }
}

void RHIShutdown()
{
  if (gRHIBackend != nullptr)
  {
    gRHIBackend->Shutdown();
    RHIGlobals::ShutdownGlobalRHIBackend(gRHIBackend);
    gRHIBackend = nullptr;
  }
}


}

}