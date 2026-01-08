#include "OpenGLDriverRHI.h"
#include "GenericPlatformOpenGLDriver.h"
#include "OpenGLDriverRHIModule.h"
#include "OpenGLResource.h"
#include "OpenGLShaders.h"
#include "OpenGLTypeTraits.h"

#include "Macro/AssertionMacros.h"
#include "Resources/RHIBufferWriter.h"
#include "RHICommandList.h"

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

  GLenum GetBufferTypeFromDesc(const MEngine::RHI::MRHIBufferDescriptor& InDesc);

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
  OPENGL_STATE_CHECK();

  const GLenum bufferType = GetBufferTypeFromDesc(Descriptor);
  if (Descriptor.IsNull())
  {
    // FIXME Wrap this inside another class to reduce human error
    // FIXME Maybe we should not new directly here?
    MOpenGLBuffer* newGLBuffer = new MOpenGLBuffer{&CmdList, bufferType, Descriptor, nullptr};
    auto defaultWriterFinalizer = [Buffer = RHIBufferRefPtr{newGLBuffer}](MEngine::RHI::MRHICommandList&) mutable -> RHIBufferRefPtr
    {
      return std::move(Buffer);
    };
    return MEngine::RHI::MRHIBufferWriter{
      &CmdList, 
      newGLBuffer, 
      nullptr, 
      0, 
      MEngine::RHI::MRHIBufferWriter::WriterFinalizer{defaultWriterFinalizer}
    };
  }

  MOpenGLBuffer* newGLBuffer = new MOpenGLBuffer{&CmdList, bufferType, Descriptor, Descriptor.BufferInitData};
  auto mapWriterFinalizer = [Buffer = RHIBufferRefPtr{newGLBuffer}](MEngine::RHI::MRHICommandList& CmdList) mutable -> RHIBufferRefPtr
  {
    CmdList.UnmapBuffer(Buffer);
    return std::move(Buffer);
  };

  // FIXME Wrap this inside another class to reduce human error
  return MEngine::RHI::MRHIBufferWriter{
    &CmdList, 
    newGLBuffer, 
    CmdList.MapBuffer(newGLBuffer, Descriptor.BufferSize, 0, MEngine::RHI::EResourceAccessMode::WriteOnly), 
    Descriptor.BufferSize, 
    MEngine::RHI::MRHIBufferWriter::WriterFinalizer{mapWriterFinalizer}
  };
}

void* MOpenGLRHIBackend::RHIMapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode)
{
  me_assert(Size > 0);
  me_assert(Buffer != nullptr);

  OPENGL_STATE_CHECK();

  MOpenGLBuffer* GLBuffer = OpenGLCast(Buffer);
  return GLBuffer->Map(Size, Offset);
}

void MOpenGLRHIBackend::RHIUnmapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer)
{
  me_assert(Buffer != nullptr);

  OPENGL_STATE_CHECK();

  MOpenGLBuffer* GLBuffer = OpenGLCast(Buffer);
  GLBuffer->Unmap();
}

RHIVertexShaderRefPtr MOpenGLRHIBackend::RHICreateVertexShader(IN std::span<const uint8> ShaderCode)
{
  return new MOpenGLVertexShader(ShaderCode);
}

void MOpenGLRHIBackend::SetVertexBufferBinding(IN uint32 SlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN uint32 Offset)
{
  me_assert(SlotIndex < MOpenGLVertexBufferBinding::MAX_BINDING_NUM);
  me_assert(VertexBuffer != nullptr);

  OPENGL_STATE_CHECK();

  // Bind Vertex for future drawing
  MOpenGLBuffer* GLBuffer = OpenGLCast(VertexBuffer);
  m_renderingState.VertexBindings[SlotIndex].VBResource = (GLBuffer != nullptr) ? GLBuffer->GLResource() : 0;
  m_renderingState.VertexBindings[SlotIndex].VBType     = (GLBuffer != nullptr) ? GLBuffer->GLType() : 0;
  m_renderingState.VertexBindings[SlotIndex].Stride     = (GLBuffer != nullptr) ? GLBuffer->GetStride() : 0;
  m_renderingState.VertexBindings[SlotIndex].Offset     = Offset; 

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

namespace
{
  GLenum GetBufferTypeFromDesc(const MEngine::RHI::MRHIBufferDescriptor& InDesc)
  {
    GLenum result = 0;

    if (!InDesc.IsNull())
    {
      const MEngine::RHI::EBufferUsageType usage = InDesc.BufferUsage;

      if (::EnumCast(usage) & ::EnumCast(MEngine::RHI::EBufferUsageType::VertexBuffer))
      {
        result = GL_ARRAY_BUFFER;
      }
      else if (::EnumCast(usage) & ::EnumCast(MEngine::RHI::EBufferUsageType::IndexBuffer))
      {
        result = GL_ELEMENT_ARRAY_BUFFER;
      }
    }

    return result;
  }
}