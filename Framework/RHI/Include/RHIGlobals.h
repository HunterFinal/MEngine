#pragma once

#ifndef _ME_RHI_CORE_RHIGLOBALS_
#define _ME_RHI_CORE_RHIGLOBALS_

#include "Macro/CPPVerMacro.h"
#include "RHIDefines.h"

namespace MEngine
{

namespace RHI
{
  class IRHIBackend;
}

}

using MEngine::RHI::IRHIBackend;

namespace RHIGlobals
{
  extern RHI_API IRHIBackend* RHIBackend;
  extern RHI_API bool IsRHIBackendInitialized;
}

#define gRHIBackend                   RHIGlobals::RHIBackend
#define gIsRHIBackendInitialized      RHIGlobals::IsRHIBackendInitialized



#endif // _ME_RHI_CORE_RHIGLOBALS_