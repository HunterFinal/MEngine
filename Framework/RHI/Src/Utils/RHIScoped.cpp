#include "Utils/RHIScoped.h"
#include "RHICommandList.h"

namespace MEngine
{

namespace RHI
{

MRHIScoped_SwitchGraphicsPipeline::MRHIScoped_SwitchGraphicsPipeline(IN MRHICommandList& CmdList)
  : m_cmdList{CmdList}
  , m_bGraphicsPipelineSet{false}
  {
    if (m_cmdList.GetPipeline() == ERHIPipeline::None)
    {
      m_cmdList.SwitchPipeline(ERHIPipeline::Graphics);
      m_bGraphicsPipelineSet = true;
    }
  }

MRHIScoped_SwitchGraphicsPipeline::~MRHIScoped_SwitchGraphicsPipeline()
{
  if (m_bGraphicsPipelineSet)
  {
    m_cmdList.SwitchPipeline(ERHIPipeline::None);
  }
}


} // namespace MEngine::RHI

} // namespace MEngine