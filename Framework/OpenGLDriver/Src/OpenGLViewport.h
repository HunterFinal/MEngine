#pragma once

#ifndef _ME_OPENGLDRV_VIEWPORT_
#define _ME_OPENGLDRV_VIEWPORT_

#include "PlatformOpenGLDriver.h"
#include "Resources/RHIViewport.h"

namespace MEngine
{

namespace OpenGLDrv
{

// Forward declaration
// Platform specific GL context
struct MOpenGLContext;

class MOpenGLViewport final : public MEngine::RHI::MRHIViewport
{

public:
  MOpenGLViewport(IN void* WindowHandle, IN uint32 Width, IN uint32 Height);
  ~MOpenGLViewport();

  /**Start MEngine::RHI::MRHIViewport interface */
  void* GetNativeWindowHandle() const override final;
  /**End MEngine::RHI::MRHIViewport interface */

  // Accessor
  MOpenGLContext* GetGLContext() const { return m_GLContext; }

  void Resize(IN uint32 NewWidth, IN uint32 NewHeight);

private:
  MOpenGLContext* m_GLContext;
  uint32 m_width;
  uint32 m_height;

};

}

}

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::OpenGLDrv::MOpenGLViewport>, GLViewportRefPtr);

#endif // _ME_OPENGLDRV_VIEWPORT_