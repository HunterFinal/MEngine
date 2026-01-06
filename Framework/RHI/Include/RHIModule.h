#pragma once

#ifndef _ME_RHI_RHIMODULE_
#define _ME_RHI_RHIMODULE_

#include "RHIDefines.h"
#include "Modules/DynamicModule.h"
#include "RHIBackend.h"

namespace MEngine
{

namespace RHI
{
  // Interface of a dynamic module implementing a RHI backend
  class IRHIModule : public MEngine::Core::IDynamicModule
  {
    public:
      virtual ~IRHIModule() = default;

      virtual bool IsSupported() const = 0;

      virtual MEngine::RHI::IRHIBackend* CreateRHIBackend() = 0;
  };

}

}


#endif // _ME_RHI_RHIMODULE_