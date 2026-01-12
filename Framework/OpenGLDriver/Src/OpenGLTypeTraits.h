#pragma once

#ifndef _ME_OPENGLDRV_TYPETRAITS_
#define _ME_OPENGLDRV_TYPETRAITS_

#include "CoreDefines.h"
#include "RHIFwd.h"
#include "OpenGLFwd.h"

// TODO We will move Requires_Derived_From to Core
#include "RHIConcepts.h"

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




}

}


#endif // _ME_OPENGLDRV_TYPETRAITS_