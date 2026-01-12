#pragma once

#ifndef _ME_OPENGLDRV_VERTEXINPUTLAYOUT_
#define _ME_OPENGLDRV_VERTEXINPUTLAYOUT_

#include "OpenGLDriverDefines.h"
#include "PlatformOpenGLDriver.h"

#include "RHITypes.h"
#include "Resources/RHIVertexInputLayout.h"

#include <array>

namespace MEngine
{

namespace OpenGLDrv
{

struct MOpenGLVertexElement
{
  GLenum GLFormat;
  GLuint Offset;
  GLuint AttribLocation;
  GLint AttribSize;
  GLboolean bNormalized;

};

struct MOpenGLVertexBufferBinding
{
  GLuint  VertexBufferResource;
  GLsizei Stride; // This must always greater than -1
  GLuint Divisor;

  constexpr MOpenGLVertexBufferBinding()
    : VertexBufferResource{0}
    , Stride{-1}
    , Divisor{0}
  { }

  MOpenGLVertexBufferBinding(IN const MEngine::RHI::MRHIVertexBinding& RHIBinding);
};

#if HAS_CPP_11
using MOpenGLVertexElements       = std::array<MEngine::OpenGLDrv::MOpenGLVertexElement, MEngine::RHI::MaxVertexElementCount>;
using MOpenGLVertexBufferBindings = std::array<MEngine::OpenGLDrv::MOpenGLVertexBufferBinding, MEngine::RHI::MaxVertexBindingCount>;
#else
typedef MOpenGLVertexElements      std::array<MEngine::OpenGLDrv::MOpenGLVertexElement, MEngine::RHI::MaxVertexElementCount>;
typedef MOpenGLVertexBufferBinding std::array<MEngine::OpenGLDrv::MOpenGLVertexBufferBinding, MEngine::RHI::MaxVertexBindingCount>;
#endif

class MOpenGLVertexInputLayout : public MEngine::RHI::MRHIVertexInputLayout
{

public:
  MOpenGLVertexInputLayout(IN const MOpenGLVertexElements& VertexElements, IN const MOpenGLVertexBufferBindings& BufferBindings)
    : GLVertexElements{VertexElements}
    , GLBindings{BufferBindings}
  { }

  MOpenGLVertexElements GLVertexElements;
  MOpenGLVertexBufferBindings GLBindings;
};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::OpenGLDrv::MOpenGLVertexInputLayout>, GLVertexInputLayoutRefPtr);


#endif // _ME_OPENGLDRV_VERTEXINPUTLAYOUT_