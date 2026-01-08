#pragma once

#ifndef _ME_OPENGLDRV_SHADERS_
#define _ME_OPENGLDRV_SHADERS_

#include "PlatformOpenGLDriver.h"
#include "Resources/RHIShaders.h"

#include <span>

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLShaderResource
{
  private: 
    friend class MOpenGLVertexShader;

    MOpenGLShaderResource(IN std::span<const uint8> ShaderCode, GLenum ShaderType);
  
  public:
    ~MOpenGLShaderResource();
    void Compile();

  public:
    GLenum Type;
    GLuint Resource;

};

class MOpenGLVertexShader : public MEngine::RHI::MRHIVertexShader
{
  public: 
    MOpenGLVertexShader(IN std::span<const uint8> ShaderCode);

    GLuint GLResource() const   { return m_shaderRes.Resource; }
    GLenum GLShaderType() const { return m_shaderRes.Type    ; }

  private:
    MOpenGLShaderResource m_shaderRes;
};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine


#endif // _ME_OPENGLDRV_SHADERS_