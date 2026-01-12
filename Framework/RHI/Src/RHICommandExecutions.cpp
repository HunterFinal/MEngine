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

void MRHISetGraphicsPSOCommand::Execute(OUT MRHIGraphicsCommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().SetGraphicsPipelineState(m_graphicsPSORef);
}

void MRHISetVertexBufferBindingCommand::Execute(OUT MRHIGraphicsCommandList& CommandList)
{
  CommandList.GetGraphicContextChecked().SetVertexBufferBinding(m_bindingSlotIndex, m_vertexBuffer, m_vertexBinding);
}

}

}