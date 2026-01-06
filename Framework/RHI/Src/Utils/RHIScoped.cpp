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
    if (m_cmdList.GetPipeline() == ERHIPipelineState::None)
    {
      m_cmdList.SwitchPipeline(ERHIPipelineState::Graphics);
      m_bGraphicsPipelineSet = true;
    }
  }

MRHIScoped_SwitchGraphicsPipeline::~MRHIScoped_SwitchGraphicsPipeline()
{
  if (m_bGraphicsPipelineSet)
  {
    m_cmdList.SwitchPipeline(ERHIPipelineState::None);
  }
}


} // namespace MEngine::RHI

} // namespace MEngine