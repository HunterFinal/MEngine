#pragma once

#ifndef _ME_OPENGLDRV_TYPETRAITS_
#define _ME_OPENGLDRV_TYPETRAITS_

#include "CoreDefines.h"
#include "RHIFwd.h"

// TODO We will move Requires_Derived_From to Core
#include "RHIConcepts.h"

namespace MEngine
{

namespace OpenGLDrv
{

// TODO Move this to Fwd header
class MOpenGLBuffer;

template<typename Type>
Requires_Derived_From(Type, MEngine::RHI::MRHIResource)
struct MOpenGLResourceTypeTraits
{
  static_assert(false, "Unexpected type of MOpenGLResourceTypeTraits");
};

template<>
struct MOpenGLResourceTypeTraits<MEngine::RHI::MRHIBuffer>
{
  TYPEDEF(MEngine::OpenGLDrv::MOpenGLBuffer, OpenGLType);
};




}

}


#endif // _ME_OPENGLDRV_TYPETRAITS_