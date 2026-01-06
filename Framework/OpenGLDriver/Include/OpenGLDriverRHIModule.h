#pragma once

#ifndef _ME_OPENGLDRV_RHIMODULE_
#define _ME_OPENGLDRV_RHIMODULE_

#include "CoreDefines.h"
#include "OpenGLDriverDefines.h"

#include "RHIModule.h"

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLDriverRHIModule final : public MEngine::RHI::IRHIModule
{

public:
  virtual ~MOpenGLDriverRHIModule() = default;

  bool IsSupported() const override;

  MEngine::RHI::IRHIBackend* CreateRHIBackend() override;
};

}

}


#endif // _ME_OPENGLDRV_RHIMODULE_