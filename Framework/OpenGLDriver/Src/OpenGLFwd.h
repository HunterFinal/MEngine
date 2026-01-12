#pragma once

#ifndef _ME_OPENGLDRV_FWD_
#define _ME_OPENGLDRV_FWD_

#include "PlatformOpenGLDriver.h"
#include "RHIConcepts.h"

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLBuffer;

template<typename RHIShaderBaseType, GLenum GLShaderTypeEnum>
Requires_Derived_From(RHIShaderBaseType, MEngine::RHI::MRHIShader)
class TOpenGLShader;



} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_FWD_