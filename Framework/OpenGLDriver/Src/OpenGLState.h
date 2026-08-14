#pragma once

#ifndef _ME_OPENGLDRV_STATE_
#define _ME_OPENGLDRV_STATE_

#include "OpenGLShaders.h"
#include "OpenGLVertexInputLayout.h"

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLLinkedShaderProgram;

struct MOpenGLDrawState
{
  MOpenGLLinkedShaderProgram* LinkedProgram = nullptr;  
  GLVertexShaderRefPtr        VertexShader  = {nullptr};
  GLPixelShaderRefPtr         PixelShader   = {nullptr};
  GLVertexInputLayoutRefPtr   InputLayout   = {nullptr};
  GLuint                      BoundVBO      = 0;
};

} // namespace MEngine::OpenGLDrv 

} // namespace MEngine


#endif // _ME_OPENGLDRV_STATE_