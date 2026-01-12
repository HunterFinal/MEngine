#pragma once

#ifndef _ME_RHI_VIEWPORT_
#define _ME_RHI_VIEWPORT_

#include "Resources/RHIResource.h"

namespace MEngine
{

namespace RHI
{

class MRHIViewport : public MEngine::RHI::MRHIResource
{
  public:
    MRHIViewport()
      : MEngine::RHI::MRHIResource{MEngine::RHI::EResourceType::Viewport}
    {}

    virtual void* GetNativeWindowHandle() const = 0;
};

} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::RHI::MRHIViewport>, RHIViewportRefPtr);

#endif // _ME_RHI_VIEWPORT_