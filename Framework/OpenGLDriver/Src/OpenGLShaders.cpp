#include "OpenGLShaders.h"

namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLShaderResource::MOpenGLShaderResource(const std::vector<const uint8> ShaderCode, GLenum ShaderType)
  : Resource{0}
{
  
}
MOpenGLShaderResource::~MOpenGLShaderResource() = default;

void MOpenGLShaderResource::Compile()
{
  
}


} // namespace MEngine::OpenGLDrv

} // namespace MEngine