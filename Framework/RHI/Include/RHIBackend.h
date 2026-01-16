#pragma once

#ifndef _ME_RHI_CORE_RHIBACKEND_
#define _ME_RHI_CORE_RHIBACKEND_

#include "RHIDefines.h"
#include "RHIConcepts.h"
#include "RHITypes.h"
#include "RHIFwd.h"
#include "Resources/RHIBuffers.h"
#include "Resources/RHIShaders.h"
#include "Resources/RHIVertexInputLayout.h"
#include "Resources/RHIPipelineState.h"
#include "Resources/RHIDescriptors.h"
#include "Resources/RHIViewport.h"
#include "Modules/DynamicModule.h"

#include <span>
#include <vector>

namespace MEngine
{

namespace RHI
{

/**
 * IRHIBackend
 * 
 * The interface which represents the active Rendering Hardware Interface backend.
 *
 * This class abstracts the underlying graphics API implementation
 * (e.g. OpenGL, Vulkan, DirectX 12)
 *
 * RHIBackend is NOT a GPU device in the strict API sense.
 * - For Vulkan / DX12, it typically wraps a VkDevice / ID3D12Device.
 * - For OpenGL, it represents the currently active graphics context
 *   and its associated global state.
 */
class IRHIBackend
{
  public:
    virtual ~IRHIBackend() = default;

    /**Initialize the RHI backend */
    virtual void Initialize() = 0;

    /**Called after the IRHIBackend::Initialize */
    virtual void PostInitialize() {}

    /**Shutdown the RHI backend. Handle internal state cleanup and resource destruction before the actual destructor is called  */
    virtual void Shutdown() = 0;
    virtual MEngine::RHI::IRHIGraphicsContext* GetDefaultGraphicsContext() = 0;

    virtual void* RHIMapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode) = 0;
    virtual void  RHIUnmapBuffer(MEngine::RHI::MRHICommandList& CmdList, IN MEngine::RHI::MRHIBuffer* Buffer) = 0;
    
    virtual MEngine::RHI::MRHIBufferWriter   RHICreateBufferWriter(IN MEngine::RHI::MRHICommandList& CmdList, IN const MEngine::RHI::MRHIBufferDescriptor& Descriptor) = 0;
    virtual RHIVertexShaderRefPtr            RHICreateVertexShader(IN std::span<const uint8> ShaderCode) = 0;
    virtual RHIPixelShaderRefPtr             RHICreatePixelShader(IN std::span<const uint8> ShaderCode) = 0;
    virtual RHIVertexInputLayoutRefPtr       RHICreateVertexInputLayout(IN const std::vector<MEngine::RHI::MRHIVertexElement>& VertexElements, IN const MEngine::RHI::MRHIVertexBindingDescriptor& BindingDesc) = 0;
    virtual RHIGraphicsPipelineStateRefPtr   RHICreateGraphicsPSO(IN const MEngine::RHI::MRHIGraphicsPipelineStateDescriptor& PSODesc) = 0;
    virtual RHIViewportRefPtr                RHICreateViewport(IN void* WindowHandle, IN uint32 Width, IN uint32 Height) = 0;
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_CORE_RHIBACKEND_