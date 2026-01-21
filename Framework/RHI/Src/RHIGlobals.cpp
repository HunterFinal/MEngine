#include "RHIGlobals.h"
#include "RHIBackend.h"

MEngine::RHI::IRHIBackend* gRHIBackend = nullptr;
bool gIsRHIBackendInitialized = false;

namespace RHIGlobals
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

    IsRHIBackendInitialized = true;
  }
}

void RHIShutdown()
{
  if (gRHIBackend != nullptr)
  {
    gRHIBackend->Shutdown();
    RHIGlobals::ShutdownGlobalRHIBackend(gRHIBackend);
    gRHIBackend = nullptr;

    IsRHIBackendInitialized = false;
  }
}

} // namespace RHIGlobals

