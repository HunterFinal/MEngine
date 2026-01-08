#include "OpenGLShaders.h"

namespace
{





}


namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLShaderResource::MOpenGLShaderResource(IN std::span<const uint8> ShaderCode, GLenum ShaderType)
  : Resource{0}
  , Type{ShaderType}
{ 

}

MOpenGLShaderResource::~MOpenGLShaderResource() = default;

void MOpenGLShaderResource::Compile()
{
  #error Start here
}

MOpenGLVertexShader::MOpenGLVertexShader(IN std::span<const uint8> ShaderCode)
  : m_shaderRes{ShaderCode, GL_VERTEX_SHADER}
{ }

} // namespace MEngine::OpenGLDrv

} // namespace MEngine