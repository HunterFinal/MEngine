#include "OpenGLDriverRHI.h"
#include "GenericPlatformOpenGLDriver.h"
#include "OpenGLDriverRHIModule.h"
#include "OpenGLResource.h"
#include "OpenGLShaders.h"
#include "OpenGLVertexInputLayout.h"
#include "OpenGLTypeTraits.h"
#include "OpenGLViewport.h"
#include "OpenGLPipelineState.h"

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
  void SetupGLFormat(OUT MEngine::OpenGLDrv::MOpenGLVertexElement& GLElement, IN MEngine::RHI::ERHIVertexFormat RHIFormat);

  static MEngine::OpenGLDrv::MOpenGLRHIBackend* g_GLBackend = nullptr;
}

extern void DeleteAllShaderResources();

namespace MEngine
{

namespace OpenGLDrv
{

MOpenGLRHIBackend::MOpenGLRHIBackend()
  : m_device{nullptr}
{
  me_assert(g_GLBackend == nullptr);
  g_GLBackend = this;
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
    MOpenGLBuffer* newGLBuffer = ::RHINewObject<MOpenGLBuffer>(&CmdList, bufferType, Descriptor, nullptr);
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

  MOpenGLBuffer* newGLBuffer = ::RHINewObject<MOpenGLBuffer>(&CmdList, bufferType, Descriptor, Descriptor.BufferInitData);
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
  return ::RHINewObject<MOpenGLVertexShader>(ShaderCode);
}

RHIPixelShaderRefPtr MOpenGLRHIBackend::RHICreatePixelShader(IN std::span<const uint8> ShaderCode)
{
  return ::RHINewObject<MOpenGLPixelShader>(ShaderCode);
}

RHIVertexInputLayoutRefPtr MOpenGLRHIBackend::RHICreateVertexInputLayout(IN const std::vector<MEngine::RHI::MRHIVertexElement>& VertexElements, IN const MEngine::RHI::MRHIVertexBindingDescriptor& BindingDesc)
{
  // Setup vertex element
  MOpenGLVertexElements GLVertexElems{};

  int32 inVertexElementCnt = VertexElements.size() <= MEngine::RHI::MaxVertexElementCount ? VertexElements.size() : MEngine::RHI::MaxVertexElementCount;
  for (int32 i = 0; i < inVertexElementCnt; ++i)
  {
    const MEngine::RHI::MRHIVertexElement& RHIElement = VertexElements[i];
    MOpenGLVertexElement& GLElement = GLVertexElems[i];
    GLElement.AttribLocation = RHIElement.Location;
    GLElement.Offset = RHIElement.Offset;
    GLElement.BindingSlotIndex = RHIElement.SlotIndex;
    SetupGLFormat(GLElement, RHIElement.Format);
  }

  // Setup vertex buffer binding
  MOpenGLVertexBufferBindings GLBufferBindings{};
  if (!BindingDesc.IsNull())
  {
    for (int32 i = 0; i < BindingDesc.GetBindingMaxSize(); ++i)
    {
      if (BindingDesc.IsBindingValid(i))
      {
        GLBufferBindings[i].Stride = BindingDesc.Bindings[i].Stride;
        
        using enum MEngine::RHI::ERHIVertexInputRate;
        switch (BindingDesc.Bindings[i].InputRate)
        {
          case PerInstance:
          {
            GLBufferBindings[i].Divisor = 1;
          }
          break;

          case PerVertex:
          {
            GLBufferBindings[i].Divisor = 0;
          }
          break;
        }
      }
    }
  }

  return ::RHINewObject<MOpenGLVertexInputLayout>(GLVertexElems, GLBufferBindings);

}

RHIGraphicsPipelineStateRefPtr MOpenGLRHIBackend::RHICreateGraphicsPSO(IN const MEngine::RHI::MRHIGraphicsPipelineStateDescriptor& PSODesc)
{
  return ::RHINewObject<MOpenGLGraphicsPipelineState>(PSODesc);
}

RHIViewportRefPtr MOpenGLRHIBackend::RHICreateViewport(IN void* WindowHandle, IN uint32 Width, IN uint32 Height)
{
  return ::RHINewObject<MOpenGLViewport>(WindowHandle, Width, Height);
}

void MOpenGLRHIBackend::SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding)
{
  me_assert(BindingSlotIndex < MEngine::RHI::MaxVertexBindingCount);
  me_assert(VertexBuffer != nullptr);
  me_assert(m_drawState.InputLayout != nullptr);

  OPENGL_STATE_CHECK();

  // Bind Vertex for future drawing
  MOpenGLBuffer* GLBuffer = OpenGLCast(VertexBuffer);

  m_drawState.InputLayout->GLBindings[BindingSlotIndex].VertexBufferResource = GLBuffer->GLResource();

}

void MOpenGLRHIBackend::SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO)
{
  MOpenGLGraphicsPipelineState* GLGraphicsPSO = OpenGLCast(GraphicsPSO);
  me_assert(GLGraphicsPSO != nullptr);

  MOpenGLVertexShader* GLVertexShader = OpenGLCast(GLGraphicsPSO->PSODescriptor.RHIVertexShader.Get());
  MOpenGLPixelShader*  GLPixelShader = OpenGLCast(GLGraphicsPSO->PSODescriptor.RHIPixelShader.Get());
  MOpenGLVertexInputLayout* GLVertexInputLayout = OpenGLCast(GLGraphicsPSO->PSODescriptor.RHIInputLayout.Get());

  SetShaderState(GLVertexShader, GLPixelShader, GLVertexInputLayout);
  m_RHIPrimitiveType = GLGraphicsPSO->PSODescriptor.PrimitiveType;
  m_GLPrimitiveType  = GLGraphicsPSO->GLPrimitiveType;
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

  // We should not call StartDrawingViewport in same frame twice before EndDrawingViewport call
  me_assert(m_drawingViewport != GLViewport);
  m_drawingViewport = GLViewport;

  // NOTE Temp
  // Switch context to current viewport
  // PlatformMakeCurrent(GLViewport->GetGLContext());
  PlatformSetupRenderTarget(GLViewport->GetGLContext());
}

void MOpenGLRHIBackend::EndDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport)
{
  me_assert(Viewport != nullptr);
  OPENGL_STATE_CHECK();

  MOpenGLViewport* GLViewport = ::OpenGLCast(Viewport);
  // We should not call StartDrawingViewport before the last
  me_assert(m_drawingViewport == GLViewport);

  PlatformSwapBuffers(GLViewport->GetGLContext());

  m_drawingViewport = nullptr;
}

void MOpenGLRHIBackend::CommitGLDrawState()
{

  {
    BindShaderState();
  }

  {
    BindVertexArrays();
  }

}

void MOpenGLRHIBackend::BindVertexArrays()
{
  OPENGL_STATE_CHECK();

  const MOpenGLVertexInputLayout* inputLayout = m_drawState.InputLayout;
  me_assert((inputLayout != nullptr) && inputLayout->GLVertexElements.size() <= MEngine::RHI::MaxVertexElementCount);

  for (int32 i = 0; i < inputLayout->GLVertexElements.size(); ++i)
  {
    const MOpenGLVertexElement& GLVertexElem = inputLayout->GLVertexElements[i];
    uint32 bindingSlotIndex = GLVertexElem.BindingSlotIndex;
    me_assert(bindingSlotIndex < inputLayout->GLBindings.size())
    const MOpenGLVertexBufferBinding& GLBinding = inputLayout->GLBindings[bindingSlotIndex];

    // Bind vertex attribute
    // Here we always bind vertex buffer.So a hardcoding is enough
    if (GLBinding.VertexBufferResource != 0)
    {
      ::glBindBuffer(GL_ARRAY_BUFFER, GLBinding.VertexBufferResource);
  
      // Start binding attribute
      ::glVertexAttribPointer(GLVertexElem.AttribLocation, GLVertexElem.AttribSize, GLVertexElem.GLFormat, GLVertexElem.bNormalized, GLBinding.Stride, (void*)GLVertexElem.Offset);
      ::glEnableVertexAttribArray(GLVertexElem.AttribLocation);
  
      // Bind divisor
      ::glVertexAttribDivisor(GLVertexElem.AttribLocation, GLBinding.Divisor);
    }
  }

}

void MOpenGLRHIBackend::RHITest_DrawTriangle()
{
    // TODO Use RHI Here
  const float vertice[] =
  {
    -0.5f, -0.5f, 0.0f,
    0.5f,  -0.5f, 0.0f,
    0.0f,   0.5f, 0.0f
  };

  const char *vertexShaderSource = "#version 460 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
  const char *fragmentShaderSource = "#version 460 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";

  {
    GLuint vao,vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
  
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
    glEnableVertexAttribArray(0);
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, nullptr);
    glCompileShader(vs);
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fs);
    
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glUseProgram(prog);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDeleteProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
  }
}

MEngine::OpenGLDrv::MOpenGLRHIBackend& GetGLBackend()
{
  me_assert(g_GLBackend != nullptr);
  return *g_GLBackend;
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

  void SetupGLFormat(OUT MEngine::OpenGLDrv::MOpenGLVertexElement& GLElement, IN MEngine::RHI::ERHIVertexFormat RHIFormat)
  {
    using enum MEngine::RHI::ERHIVertexFormat;
    switch (RHIFormat)
    {
      case Float2:
      {
        GLElement.GLFormat = GL_FLOAT;
        GLElement.AttribSize = 2;
        GLElement.bNormalized = GL_FALSE;
      }
      break;
      case Float3:
      {
        GLElement.GLFormat = GL_FLOAT;
        GLElement.AttribSize = 3;
        GLElement.bNormalized = GL_FALSE;
      }
      break;

      //
      default:
      {
        me_assert(false);
      }
      break;
    }
  }

} // nameless namespace

