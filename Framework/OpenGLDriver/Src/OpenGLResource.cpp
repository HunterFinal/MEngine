#include "OpenGLResource.h"
#include "OpenGLCommands.h"
#include "OpenGLDriverRHI.h"
#include "RHICommandList.h"

namespace MEngine
{

namespace OpenGLDrv
{

void MOpenGLResource::Bind()
{
  OPENGL_STATE_CHECK();

  GetGLBackend().GLBindBuffer(Type, Resource);

}

void MOpenGLResource::OnDeleted()
{
  OPENGL_STATE_CHECK();

  GetGLBackend().GLOnBufferDeleted(Type, Resource);
}

MOpenGLBuffer::MOpenGLBuffer(IN MEngine::RHI::MRHICommandList* CmdList, IN GLenum BufferType, IN const MEngine::RHI::MRHIBufferDescriptor& Descriptor, IN const void* Data)
  : MEngine::RHI::MRHIBuffer{Descriptor}
  , m_mappingState{nullptr, 0, 0, false}
  , m_nativeResource{BufferType}
  , m_bIsMapping{false}
{
  if (CmdList != nullptr && CmdList->IsRecording() && Data != nullptr)
  {
    Data = CmdList->AllocMemcpy(Data, Descriptor.BufferSize, 16);
  }

  if (!Descriptor.IsNull())
  {
    if (CmdList != nullptr)
    {
      (void)CmdList->AllocCommandAndConstruct<MEngine::OpenGLDrv::MOpenGLBufferInitializationCommand>(this, Data);
    }
    else
    {
      MEngine::RHI::MRHICommandList dummy{};
      MEngine::OpenGLDrv::MOpenGLBufferInitializationCommand{this, Data}.Execute(dummy);
    }
  }
} 

MOpenGLBuffer::~MOpenGLBuffer()
{
  ReleaseResource();
}

void MOpenGLBuffer::BindToOpenGL()
{
  m_nativeResource.Bind();
}

void* MOpenGLBuffer::MOpenGLBuffer::Map(IN uint32 InSize, IN uint32 InOffset)
{
  // Overflow check
  me_assert(InSize + InOffset <= GetDesc().BufferSize);

  // Mapping is not allowed twice
  me_assert(!m_bIsMapping);

  OPENGL_STATE_CHECK()

  // Bind resource to OpenGL
  BindToOpenGL();
  m_bIsMapping = true;

  void* dest = nullptr;

  m_mappingState.MapSize = InSize;
  m_mappingState.MapOffset = InOffset;
  m_mappingState.MapData = ::malloc(InSize);
  m_mappingState.bWasMapDataAllocated = true;
  dest = m_mappingState.MapData;

  return dest;
}

void MOpenGLBuffer::Unmap()
{
  OPENGL_STATE_CHECK();
  if (m_bIsMapping)
  {
    BindToOpenGL();

    ::glBufferSubData(m_nativeResource.Type, m_mappingState.MapOffset, m_mappingState.MapSize, m_mappingState.MapData);

    ::free(m_mappingState.MapData);
    m_mappingState.MapData = nullptr;
    m_mappingState.MapSize = 0;
    m_mappingState.MapOffset = 0;
    m_mappingState.bWasMapDataAllocated = false;

    m_bIsMapping = false;
  }
}

void MOpenGLBuffer::ReleaseResource()
{
  // Can not release resource during mapping
  me_assert(!m_bIsMapping);
  OPENGL_STATE_CHECK();

  // Delete opengl resource
  if (m_nativeResource.Resource != 0)
  {
    m_nativeResource.OnDeleted();

    ::glDeleteBuffers(1, &m_nativeResource.Resource);
    m_nativeResource.Resource = 0;
  }
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine