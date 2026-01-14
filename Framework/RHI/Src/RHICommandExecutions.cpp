#include "RHICommand.h"
#include "RHICommandList.h"

namespace MEngine
{

namespace RHI
{

IRHICommand::~IRHICommand() = default;

void MRHIDrawPrimitiveCommand::Execute(OUT MRHICommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().DrawPrimitive(m_startVertexIndex, m_primitiveNum, m_instanceNum);
}

void MRHISetGraphicsPSOCommand::Execute(OUT MRHICommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().SetGraphicsPipelineState(m_graphicsPSORef);
}

void MRHISetVertexBufferBindingCommand::Execute(OUT MRHICommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().SetVertexBufferBinding(m_bindingSlotIndex, m_vertexBuffer, m_vertexBinding);
}

void MRHIStartDrawingViewportCommand::Execute(OUT MRHICommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().StartDrawingViewport(m_viewport);
}

void MRHIEndDrawingViewportCommand::Execute(OUT MRHICommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().EndDrawingViewport(m_viewport);
}

} // namespace MEngine::RHI

} // namespace MEngine