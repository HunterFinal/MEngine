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

}

}