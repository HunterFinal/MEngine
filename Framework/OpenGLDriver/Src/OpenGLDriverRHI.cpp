#include "OpenGLDriverRHI.h"
#include "GenericPlatformOpenGLDriver.h"
#include "OpenGLDriverRHIModule.h"
#include "OpenGLResource.h"
#include "OpenGLShaders.h"
#include "OpenGLVertexInputLayout.h"
#include "OpenGLTypeTraits.h"
#include "OpenGLViewport.h"

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
  GLsizei GetElementNumOfGLPrimitive(IN const uint32 PrimitiveNum, IN const GLenum GLPrimitiveType);

  class MOpenGLScope_PlatformMakeCurrentContext final
  {
    public:
      MOpenGLScope_PlatformMakeCurrentContext(IN MEngine::OpenGLDrv::MOpenGLViewport* Viewport)
        : m_viewport{Viewport}
      {
        me_assert(Viewport != nullptr);
        MEngine::OpenGLDrv::PlatformMakeCurrent(Viewport->GetGLContext());
      }

      ~MOpenGLScope_PlatformMakeCurrentContext()
      {
        MEngine::OpenGLDrv::PlatformMakeCurrent(nullptr);
      }

    private:
      GLViewportRefPtr m_viewport;
  };

}

extern void DeleteAllShaderResources();

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
  DeleteAllShaderResources();
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

RHIPixelShaderRefPtr MOpenGLRHIBackend::RHICreatePixelShader(IN std::span<const uint8> ShaderCode)
{
  return new MOpenGLPixelShader(ShaderCode);
}

RHIVertexInputLayoutRefPtr MOpenGLRHIBackend::RHICreateVertexInputLayout(IN const std::vector<MEngine::RHI::MRHIVertexElement>& VertexElements, IN const MEngine::RHI::MRHIVertexBindingDescriptor& BindingDesc)
{

}

void MOpenGLRHIBackend::SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding)
{
  me_assert(BindingSlotIndex < MEngine::RHI::MAX_STAGE_NUM);
  me_assert(VertexBuffer != nullptr);

  OPENGL_STATE_CHECK();

  // Bind Vertex for future drawing
  MOpenGLBuffer* GLBuffer = OpenGLCast(VertexBuffer);

  #error Bind to cache

}

void MOpenGLRHIBackend::SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO)
{

}

void MOpenGLRHIBackend::DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
{
  OPENGL_STATE_CHECK();

  const uint32 vertexCount = RHIHelper::GetVertexCountOfPrimitiveType(PrimitiveNum, m_RHIPrimitiveType);

  CommitGLDrawState();
  GLsizei elementNumToDraw = GetElementNumOfGLPrimitive(PrimitiveNum, m_GLPrimitiveType);

  if (InstanceNum == 1)
  {
    ::glDrawArrays(m_GLPrimitiveType, 0, elementNumToDraw);
  }
  else
  {
    ::glDrawArraysInstanced(m_GLPrimitiveType, 0, elementNumToDraw, InstanceNum);
  }
}

void MOpenGLRHIBackend::DrawPrimitiveIndexed(IN MEngine::RHI::MRHIBuffer* IndexBuffer, IN uint32 StartVertexIndex, IN uint32 StartIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
{
  // FIXME
}

void MOpenGLRHIBackend::StartDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport)
{
  me_assert(Viewport != nullptr);
  OPENGL_STATE_CHECK();

  MOpenGLViewport* GLViewport = ::OpenGLCast(Viewport);

  // Switch context to current viewport
  PlatformMakeCurrent(GLViewport->GetGLContext());
}

void MOpenGLRHIBackend::EndDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport)
{

}

void MOpenGLRHIBackend::CommitGLDrawState()
{
  #error Setup draw state by cached context state
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

  GLsizei GetElementNumOfGLPrimitive(IN const uint32 PrimitiveNum, IN const GLenum GLPrimitiveType)
  {
    GLsizei result = PrimitiveNum;

    switch (GLPrimitiveType)
    {
      case GL_TRIANGLES:
      {
        result *= 3;
      }
      break;

      default:
      {
        me_assert(false);
      }
      break;
    }

    return result;
  }

} // nameless namespace