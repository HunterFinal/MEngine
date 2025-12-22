#include "Core/RHICore.h"
#include "RHIGlobals.h"
#include "RHIPlatform.h"
#include "Core/RHIBackend.h"

namespace MEngine
{

namespace RHI
{

void RHIInitialize()
{
  if (gRHIBackend == nullptr)
  {
    gRHIBackend = RHIPlatform::CreateRHIBackend();

    if (gRHIBackend != nullptr)
    {
      gRHIBackend->Initialize();
    }
  }
}

void RHIShutdown()
{

}

}

}