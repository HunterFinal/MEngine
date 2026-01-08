#pragma once

#ifndef _ME_RHI_CORE_RHIGLOBALS_
#define _ME_RHI_CORE_RHIGLOBALS_

#include "RHIDefines.h"

namespace MEngine
{
namespace RHI
{
  class IRHIBackend;
}
}

namespace RHIGlobals
{
  extern RHI_API MEngine::RHI::IRHIBackend* GlobalRHIBackend;
  extern RHI_API bool IsRHIBackendInitialized;

  RHI_API void RHIInitialize();

  RHI_API void RHIShutdown(); 

  RHI_API MEngine::RHI::IRHIBackend* CreateGlobalRHIBackend();

  RHI_API void ShutdownGlobalRHIBackend(MEngine::RHI::IRHIBackend* RHIBackend);
}

#define gRHIBackend                   RHIGlobals::GlobalRHIBackend
#define gIsRHIBackendInitialized      RHIGlobals::IsRHIBackendInitialized



#endif // _ME_RHI_CORE_RHIGLOBALS_