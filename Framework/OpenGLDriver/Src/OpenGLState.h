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
  MOpenGLLinkedShaderProgram* LinkedProgram;  
  GLVertexShaderRefPtr        VertexShader;
  GLPixelShaderRefPtr         PixelShader;
  GLVertexInputLayoutRefPtr   InputLayout;
  GLuint                      BoundVBO;
};

} // namespace MEngine::OpenGLDrv 

} // namespace MEngine


#endif // _ME_OPENGLDRV_STATE_