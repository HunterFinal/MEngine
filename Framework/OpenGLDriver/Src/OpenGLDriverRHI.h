#pragma once

#ifndef _ME_OPENGLDRV_RHI_
#define _ME_OPENGLDRV_RHI_

#include "OpenGLDriverDefines.h"
#include "OpenGLUtils.h"
#include "PlatformOpenGLDriver.h"

#include "RHITypes.h"
#include "RHIBackend.h"
#include "RHIContext.h"
#include "Utils/RHIHelper.h"

namespace MEngine
{

namespace OpenGLDrv
{

struct MOpenGLDevice;

class MOpenGLRHIBackend final : public MEngine::RHI::IRHIBackend, public MEngine::RHI::IRHIGraphicsContext
{
public:
  OPENGLDRV_API MOpenGLRHIBackend();
  OPENGLDRV_API ~MOpenGLRHIBackend() = default;

  /**Start IRHIBackend interface */
  OPENGLDRV_API void Initialize() override final;
  OPENGLDRV_API void Shutdown() override final;
  OPENGLDRV_API MEngine::RHI::IRHIGraphicsContext* GetDefaultGraphicsContext() override final;
  OPENGLDRV_API MEngine::RHI::MRHIBufferWriter RHICreateBufferWriter(MEngine::RHI::MRHICommandList& CmdList, IN const MEngine::RHI::MRHIBufferDescriptor& Descriptor) override final;
  OPENGLDRV_API void* RHIMapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode) override final;
  OPENGLDRV_API void RHIUnmapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer) override final;
  OPENGLDRV_API RHIVertexShaderRefPtr RHICreateVertexShader(IN std::span<const uint8> ShaderCode) override final;
  OPENGLDRV_API RHIPixelShaderRefPtr RHICreatePixelShader(IN std::span<const uint8> ShaderCode) override final;
  OPENGLDRV_API RHIVertexInputLayoutRefPtr RHICreateVertexInputLayout(IN const std::vector<MEngine::RHI::MRHIVertexElement>& VertexElements, IN const MEngine::RHI::MRHIVertexBindingDescriptor& BindingDesc) override final;
  /**End IRHIBackend interface */

  /**Start IRHIGraphicsContext interface */
  OPENGLDRV_API void SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding) override final;
  OPENGLDRV_API void SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO) override final;
  OPENGLDRV_API void DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum) override final;
  OPENGLDRV_API void DrawPrimitiveIndexed(IN MEngine::RHI::MRHIBuffer* IndexBuffer, IN uint32 StartVertexIndex, IN uint32 StartIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum) override final;
  /**End IRHIGraphicsContext interface */

private:
  void CommitGLDrawState();

private:
  MOpenGLDevice* m_device;

  MEngine::RHI::EPrimitiveTopologyType m_RHIPrimitiveType;
  GLenum                               m_GLPrimitiveType;

};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine

#endif // _ME_OPENGLDRV_RHI_