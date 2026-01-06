#include "OpenGLDriverRHI.h"
#include "GenericPlatformOpenGLDriver.h"
#include "OpenGLDriverRHIModule.h"
#include "OpenGLResource.h"
#include "Resources/RHIBufferWriter.h"
#include "OpenGLTypeTraits.h"

#include "Macro/AssertionMacros.h"

// TODO
#include <iostream>

namespace
{
  template<typename RHIResourceType>
  Requires_Derived_From(RHIResourceType, MEngine::RHI::MRHIResource)
  auto* OpenGLCast(RHIResourceType* Resource)
  {
    return static_cast<typename MEngine::OpenGLDrv::MOpenGLResourceTypeTraits<RHIResourceType>::OpenGLType*>(Resource);
  };

}

namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLRHIBackend::MOpenGLRHIBackend()
  : m_device{nullptr}
{
  const bool bInitSuccess = InitOpenGL();
  me_assert(bInitSuccess);
  m_device = CreateOpenGLDevice();
  me_assert(m_device != nullptr);

  // We must ensure the opengl is fully initialized here to continue
  OPENGL_STATE_CHECK();
}

void MOpenGLRHIBackend::Initialize()
{
  std::cout << "OpenGL RHI Backend Initialize" << std::endl;
}

void MOpenGLRHIBackend::Shutdown()
{
  std::cout << "OpenGL RHI Backend Shutdown" << std::endl;
}

MEngine::RHI::IRHIGraphicsContext* MOpenGLRHIBackend::GetDefaultGraphicsContext()
{
  return this;
}

MEngine::RHI::MRHIBufferWriter MOpenGLRHIBackend::RHICreateBufferWriter(MEngine::RHI::MRHICommandList& CmdList, const MEngine::RHI::MRHIBufferDescriptor& Descriptor)
{
  return MEngine::RHI::MRHIBufferWriter::InvalidWriter;
}

void* MOpenGLRHIBackend::RHIMapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode)
{
  me_assert(Size > 0);
  OPENGL_STATE_CHECK();

  MOpenGLBuffer* GLBuffer = OpenGLCast(Buffer);

  return GLBuffer->Map(Size, Offset);
}

void MOpenGLRHIBackend::RHIUnmapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer)
{
  OPENGL_STATE_CHECK();

  MOpenGLBuffer* GLBuffer = OpenGLCast(Buffer);

  GLBuffer->Unmap();
}

void MOpenGLRHIBackend::SetVertexBuffer(IN uint32 SlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN uint32 Offset)
{
  // FIXME
  #error Start here
}

void MOpenGLRHIBackend::DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
{
  OPENGL_STATE_CHECK();

  m_ptType = MEngine::RHI::EPrimitiveTopologyType::TriangleList;

  const uint32 vertexCount = RHIHelper::GetVertexCountOfPrimitiveType(PrimitiveNum, m_ptType);

  if (InstanceNum == 1)
  {
    // glDrawArrays();
  }
}

void MOpenGLRHIBackend::DrawPrimitiveIndexed(IN MEngine::RHI::MRHIBuffer* IndexBuffer, IN uint32 StartVertexIndex, IN uint32 StartIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
{
  // FIXME
}


} // namespace MEngine::OpenGLDrv

} // namespace MEngine