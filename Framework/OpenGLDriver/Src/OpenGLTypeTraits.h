#pragma once

#ifndef _ME_OPENGLDRV_TYPETRAITS_
#define _ME_OPENGLDRV_TYPETRAITS_

#include "CoreDefines.h"
#include "RHIFwd.h"
#include "RHITypes.h"
#include "RHIConcepts.h"

#include "OpenGLFwd.h"

namespace MEngine
{

namespace OpenGLDrv
{

template<typename Type>
Requires_Derived_From(Type, MEngine::RHI::MRHIResource)
struct MOpenGLResourceTypeTraits
{ };

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIBuffer>
{
  using OpenGLType = MEngine::OpenGLDrv::MOpenGLBuffer;
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIVertexShader>
{
  using OpenGLType = MEngine::OpenGLDrv::TOpenGLShader<MEngine::RHI::MRHIVertexShader, GL_VERTEX_SHADER>;
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIPixelShader>
{
  using OpenGLType = MEngine::OpenGLDrv::TOpenGLShader<MEngine::RHI::MRHIPixelShader, GL_FRAGMENT_SHADER>;
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIViewport>
{
  using OpenGLType = MEngine::OpenGLDrv::MOpenGLViewport;
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIGraphicsPipelineState>
{
  using OpenGLType = MEngine::OpenGLDrv::MOpenGLGraphicsPipelineState;
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIVertexInputLayout>
{
  using OpenGLType = MEngine::OpenGLDrv::MOpenGLVertexInputLayout;
};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_TYPETRAITS_