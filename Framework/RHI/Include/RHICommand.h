#pragma once

#ifndef _ME_RHI_COMMAND_
#define _ME_RHI_COMMAND_

#include "RHIDefines.h"
#include "RHIConcepts.h"

#include <type_traits>
#include <utility>
#include <atomic>

#define RHI_COMMAND_CHECK 1

namespace MEngine
{

namespace RHI
{

// Forward declaration
class MRHICommandList;

class IRHICommand
{
  public:
    RHI_API virtual ~IRHICommand();
    virtual void ExecuteAndDispose(OUT MRHICommandList& CommandList) = 0;

    IRHICommand* Next = nullptr;
};

template<typename RHICmdListType, typename LambdaType> 
Requires_RHICommand_Callable(RHICmdListType, LambdaType)
class MRHILambdaCommand final : public IRHICommand
{

#if !CAN_USE_CONCEPT
  #if HAS_CPP_14
    static_assert(std::is_base_of<MRHICommandList, RHICmdListType>::value,"The command list type should derived from MEngine::RHI::MRHICommandList");
  #endif
#endif

public:
  MRHILambdaCommand(IN LambdaType&& Lambda)
    : m_lambda{std::forward<LambdaType>(Lambda)}
#if RHI_COMMAND_CHECK
    , m_bCommandExecuted{false}
#endif
  {}

  void ExecuteAndDispose(OUT MRHICommandList& CommandList) override final
  {

#if RHI_COMMAND_CHECK
    bool bIsExecutedBefore = m_bCommandExecuted.load(std::memory_order_acquire);
    me_assert(!bIsExecutedBefore);
    if (bIsExecutedBefore)
    {
      return;
    }
#endif 

    Execute(static_cast<RHICmdListType&>(CommandList));

#if RHI_COMMAND_CHECK
    m_bCommandExecuted.store(true, std::memory_order_release);
#endif
    // Destruct all captures in lambda
    // We manage the IRHICommand memory ourselves by using placement new.
    // So we call this here
    m_lambda.~LambdaType();
  }

private:
  void Execute(OUT RHICmdListType& CommandList)
  {
    m_lambda.operator()(CommandList);
  }

private:
  LambdaType m_lambda;

#if RHI_COMMAND_CHECK
  std::atomic_bool m_bCommandExecuted;
#endif

};

// CRTP
template<typename CmdType>
class TRHICommand : public IRHICommand
{

public:
  void ExecuteAndDispose(OUT MRHICommandList& CommandList) override final
  {
    CmdType* specificCmd = static_cast<CmdType*>(this);
    specificCmd->Execute(CommandList);
    specificCmd->~CmdType();
  }

  ~TRHICommand() = default;
};

class MRHIDrawPrimitiveCommand : public TRHICommand<MRHIDrawPrimitiveCommand>
{
  public:
    MRHIDrawPrimitiveCommand(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
      : m_startVertexIndex{StartVertexIndex}
      , m_primitiveNum{PrimitiveNum}
      , m_instanceNum{InstanceNum}
    { }

    void Execute(OUT MRHICommandList& CommandList);

  private:
    uint32 m_startVertexIndex;
    uint32 m_primitiveNum;
    uint32 m_instanceNum;
};

class MRHISetGraphicsPSOCommand : public TRHICommand<MRHISetGraphicsPSOCommand>
{
  public:
    MRHISetGraphicsPSOCommand(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO)
      : m_graphicsPSORef{GraphicsPSO}
    { }

    void Execute(OUT MRHIGraphicsCommandList& CommandList);

  private:
    RHIGraphicsPipelineStateRefPtr m_graphicsPSORef;
};

class MRHISetVertexBufferBindingCommand : public TRHICommand<MRHISetVertexBufferBindingCommand>
{
  public:
    MRHISetVertexBufferBindingCommand(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding)
      : m_bindingSlotIndex{BindingSlotIndex}
      , m_vertexBuffer{VertexBuffer}
      , m_vertexBinding{VertexBinding}
    { }

    void Execute(OUT MRHIGraphicsCommandList& CommandList);

  private:
    uint32 m_bindingSlotIndex;
    RHIBufferRefPtr m_vertexBuffer;
    MRHIVertexBinding m_vertexBinding;
};

} // namespace MEngine::RHI

} // namespace MEngine

#undef RHI_COMMAND_CHECK

#endif // _ME_RHI_COMMAND_