#pragma once

#ifndef _ME_RHI_CORE_RHICONTEXT_
#define _ME_RHI_CORE_RHICONTEXT_

#include "RHIDefines.h"

namespace MEngine
{

namespace RHI
{

class MRHIBuffer;

/**
 * IRHIGraphicsContext
 * 
 * This interface represents a graphics-only rendering context in RHI layer
 * 
 * // TODO Need more description
 * 
 */
class IRHIGraphicsContext
{
  public:
    RHI_API ~IRHIGraphicsContext() = default;

    virtual void SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding) = 0;
    virtual void SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO) = 0;
    virtual void DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum) = 0;
    virtual void DrawPrimitiveIndexed(IN MEngine::RHI::MRHIBuffer* IndexBuffer, IN uint32 StartVertexIndex, IN uint32 StartIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum) = 0;
    virtual void StartDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport) = 0;
    virtual void EndDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport) = 0;
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_CORE_RHICONTEXT_