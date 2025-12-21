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

extern RHI_API IRHIBackend* gRHIBackend;

#endif // _ME_RHI_CORE_RHIGLOBALS_