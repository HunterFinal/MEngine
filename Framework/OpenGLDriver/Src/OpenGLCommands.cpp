#include "OpenGLCommands.h"
#include "OpenGLResource.h"
#include "RHICommandList.h"
#include "OpenGLUtils.h"

namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLBufferInitializationCommand::MOpenGLBufferInitializationCommand(IN MOpenGLBuffer* InBuffer, IN const void* InData)
  : m_buffer{InBuffer}
  , m_data{InData}
{
  me_assert(InBuffer != nullptr);
}

MOpenGLBufferInitializationCommand::~MOpenGLBufferInitializationCommand()
{
  m_buffer = nullptr;
  m_data = nullptr;
}

void MOpenGLBufferInitializationCommand::Execute(OUT MEngine::RHI::MRHICommandList& CommandList)
{
  OPENGL_STATE_CHECK();

  ::glGenBuffers(1, m_buffer->GLResourceAddress());

  m_buffer->BindToOpenGL();

  ::glBufferData(m_buffer->GLType(), m_buffer->GetSize(), m_data, m_buffer->GLUsage());
}

}

}