#pragma once

#ifndef _ME_OPENGLDRV_SHADERS_
#define _ME_OPENGLDRV_SHADERS_

#include "PlatformOpenGLDriver.h"

// TODO 
#include <vector>

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLShaderResource
{
  private: 
    friend class MOpenGLVertexShader;

    MOpenGLShaderResource(const std::vector<const uint8> ShaderCode, GLenum ShaderType);
    ~MOpenGLShaderResource();

    void Compile();

  public:
    GLuint Resource;

};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_SHADERS_