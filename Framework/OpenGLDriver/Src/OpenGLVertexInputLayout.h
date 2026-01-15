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
  // Specifies the type of vertex data
  GLenum GLFormat;

  // Offset of where the position data begins
  GLuint Offset;

  // Specifies which vertex attribute we want to configure
  GLuint AttribLocation;

  // Size of the vertex attribute
  GLint AttribSize;

  // Specifies if we want the data to be normalized
  GLboolean bNormalized;

  // Specifies which vertex buffer binding we want to reference
  uint8 BindingSlotIndex;

};

struct MOpenGLVertexBufferBinding
{
  GLuint  VertexBufferResource;
  GLsizei Stride; // This must always greater than -1
  GLuint Divisor;

  constexpr MOpenGLVertexBufferBinding()
    : VertexBufferResource{0}
    , Stride{0}
    , Divisor{0}
  { }
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