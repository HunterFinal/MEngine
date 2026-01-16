#include "OpenGLDriverRHI.h"

namespace MEngine
{

namespace OpenGLDrv
{

void MOpenGLRHIBackend::GLBindBuffer(IN GLenum BufferType, IN GLuint BufferResource)
{
  OPENGL_STATE_CHECK();

  switch (BufferType)
  {
    case GL_ARRAY_BUFFER:
    {
      if (m_drawState.BoundVBO != BufferResource)
      {
        ::glBindBuffer(GL_ARRAY_BUFFER, BufferResource);
        m_drawState.BoundVBO = BufferResource;
      }
    }
    break;
  }
}

void MOpenGLRHIBackend::GLOnBufferDeleted(IN GLenum BufferType, IN GLuint BufferResource)
{
  OPENGL_STATE_CHECK();

  switch(BufferType)
  {
    case GL_ARRAY_BUFFER:
    {
      if (m_drawState.BoundVBO == BufferResource)
      {
        m_drawState.BoundVBO = 0;
      }
      ::glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    break;
  }

  if (m_drawState.InputLayout != nullptr)
  {
    // Disable all vertex buffer binding
    for (MOpenGLVertexBufferBinding& GLBinding : m_drawState.InputLayout->GLBindings)
    {
      if (GLBinding.VertexBufferResource == BufferResource)
      {
        GLBinding.VertexBufferResource = 0;
        GLBinding.Stride = 0;
        GLBinding.Divisor = 0;
      }
    }

  }

}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine