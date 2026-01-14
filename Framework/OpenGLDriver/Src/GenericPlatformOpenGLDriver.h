#pragma once

#ifndef _ME_OPENGLDRV_GENERIC_PLATFORM_
#define _ME_OPENGLDRV_GENERIC_PLATFORM_

#include "OpenGLDriverRHI.h"

namespace MEngine
{

namespace OpenGLDrv
{

// Forward declaration
// Platform specific device
// MEngine::OpenGLDrv::MOpenGLDevice
struct MOpenGLDevice;

// Platform specific context
// MEngine::OpenGLDrv::MOpenGLContext
struct MOpenGLContext;

class  MOpenGLViewport;

// Platform specific global function declaration
bool InitOpenGL();

int32 GLGetLastError();

MEngine::OpenGLDrv::MOpenGLDevice* CreateOpenGLDevice();

void DestroyOpenGLDevice(IN MEngine::OpenGLDrv::MOpenGLDevice* Device);

MEngine::OpenGLDrv::MOpenGLContext* CreateOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLDevice* Device, IN void* WindowHandle);

void DestroyOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLContext* Context);

// Returns true when opengl rendering context exist
bool GLHasRenderingContext();

// Returns the pointer to the platform specific window handle
void* GetNativeWindow(IN MEngine::OpenGLDrv::MOpenGLContext* GLContext);

bool  BlitToViewport(IN MEngine::OpenGLDrv::MOpenGLDevice* Device, IN MEngine::OpenGLDrv::MOpenGLViewport* Viewport, IN uint32 Width, IN uint32 height);

// Make current opengl context
void  PlatformMakeCurrent(IN MEngine::OpenGLDrv::MOpenGLContext* GLContext);
void  PlatformSwapBuffers(IN MEngine::OpenGLDrv::MOpenGLContext* GLContext);


} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_GENERIC_PLATFORM_