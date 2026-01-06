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

// Platform specific global function declaration
bool InitOpenGL();

int32 GLGetLastError();

MEngine::OpenGLDrv::MOpenGLDevice* CreateOpenGLDevice();

void DestroyOpenGLDevice(IN MEngine::OpenGLDrv::MOpenGLDevice* Device);

MEngine::OpenGLDrv::MOpenGLContext* CreateOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLDevice* Device, IN void* WindowHandle);

void DestroyOpenGLContext(IN MEngine::OpenGLDrv::MOpenGLContext* Context);

// Returns true when opengl rendering context exist
bool GLHasRenderingContext();

} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_GENERIC_PLATFORM_