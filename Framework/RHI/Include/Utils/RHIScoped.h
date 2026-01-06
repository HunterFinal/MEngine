#pragma once

#ifndef _ME_RHI_SCOPED_
#define _ME_RHI_SCOPED_

#include "CoreDefines.h"

namespace MEngine
{

namespace RHI
{

class MRHICommandList;

class MRHIScoped_SwitchGraphicsPipeline
{
  
public:
  MRHIScoped_SwitchGraphicsPipeline(IN MRHICommandList& CmdList);
  ~MRHIScoped_SwitchGraphicsPipeline();

private:
  MRHICommandList& m_cmdList;
  bool m_bGraphicsPipelineSet;
};

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_SCOPED_