#pragma once

#ifndef _ME_OPENGLDRV_STATE_
#define _ME_OPENGLDRV_STATE_

#include "OpenGLDriverDefines.h"
#include "PlatformOpenGLDriver.h"

namespace MEngine
{

namespace OpenGLDrv
{

struct MOpenGLVertexBufferBinding
{
  constexpr static int32 MAX_BINDING_NUM = 16;

  GLenum VBResource;
  GLenum VBType;
  uint32 Offset;
  uint32 Stride;

  constexpr MOpenGLVertexBufferBinding()
    : VBResource{0}
    , VBType{0}
    , Offset{0}
    , Stride{0}
  { }
};

#if HAS_CPP_11
using MOpenGLVertexBufferBindings = MOpenGLVertexBufferBinding[MOpenGLVertexBufferBinding::MAX_BINDING_NUM];
#else
typedef MOpenGLVertexBufferBinding MOpenGLVertexBufferBindings[MOpenGLVertexBufferBinding::MAX_BINDING_NUM];
#endif

struct MOpenGLRenderingState
{
  MOpenGLVertexBufferBindings VertexBindings;
};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_STATE_