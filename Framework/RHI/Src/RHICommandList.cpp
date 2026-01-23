#include "RHICommandList.h"
#include "RHIGlobals.h"
#include "RHIBackend.h"

#include "Utils/RHICommandIterator.h"
#include "Utils/RHIScoped.h"
#include "Resources/RHIBufferWriter.h"

namespace MEngine::RHI::Internal
{
  extern void FlushResourcesToDelete();
}

namespace MEngine
{

namespace RHI
{

MRHICommandList::MRHICommandChain::MRHICommandChain()
  : Root{nullptr}
  , Tail{nullptr}
  , CommandNum{0}
{
  Tail = &Root;
}

void MRHICommandList::MRHICommandChain::PushBack(IN IRHICommand* NewCmd)
{
  *Tail = NewCmd;
  Tail = &NewCmd->Next;
  ++CommandNum;
}

MRHICommandIterator MRHICommandList::MRHICommandChain::begin()
{
  return MEngine::RHI::MRHICommandIterator{Root};
}

MRHICommandIterator MRHICommandList::MRHICommandChain::end()
{
  return MEngine::RHI::MRHICommandIterator{ (*Tail != nullptr) ? (*Tail)->Next : nullptr };
}

MRHICommandList::MRHICommandList()
  : m_bIsExecuting{false}
  , m_bIsImmediate{false}
{ }

MRHICommandList::~MRHICommandList()
{
  // Delete resources that reference count reach 0
  MEngine::RHI::Internal::FlushResourcesToDelete();
}

void* MRHICommandList::AllocCommandInternal(IN SIZE_T AllocSize, IN SIZE_T Alignment)
{
  me_assert(!IsExecuting());
  me_assert(IsRecording());

  IRHICommand* newCmd = reinterpret_cast<IRHICommand*>(m_memoryManager.Allocate(AllocSize, Alignment));
  m_commandChain.PushBack(newCmd);

  return newCmd;
}

bool MRHICommandList::IsRecording() const
{
  return !ShouldExecuteImmediatly();
}

bool MRHICommandList::IsExecuting() const
{
  return m_bIsExecuting;
}

bool MRHICommandList::IsImmediate() const
{
  return m_bIsImmediate;
}

bool MRHICommandList::ShouldExecuteImmediatly() const
{
  return IsImmediate() || IsExecuting();
}

bool MRHICommandList::HasAnyCommand() const
{
  return m_memoryManager.IsEmpty();
}

ERHIPipeline MRHICommandList::GetPipeline() const
{
  return m_activatePipeline;
}

IRHIGraphicsContext& MRHICommandList::GetGraphicContextChecked()
{
  me_assert(m_graphicContext != nullptr);
  return *m_graphicContext;
}

void MRHICommandList::ExecuteCommands()
{
  me_assert(!IsExecuting());
  m_bIsExecuting = true;

  for (IRHICommand& CmdRef : m_commandChain)
  {
    CmdRef.ExecuteAndDispose(*this);
  }
}

void MRHICommandList::SwitchPipeline(ERHIPipeline NewPipeline)
{
  if (GetPipeline() == NewPipeline)
  {
    return;
  }

  ActivatePipeline(NewPipeline);
}

MEngine::RHI::MRHIBufferWriter MRHICommandList::CreateBufferWriter(const MRHIBufferDescriptor& Descriptor)
{
  MRHIScoped_SwitchGraphicsPipeline scoped{*this};
  return gRHIBackend->RHICreateBufferWriter(*this, Descriptor);
}

void* MRHICommandList::MapBuffer(MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode)
{
  MRHIScoped_SwitchGraphicsPipeline scoped{*this};
  return gRHIBackend->RHIMapBuffer(*this, Buffer, Size, Offset, AccessMode);
}

void MRHICommandList::UnmapBuffer(MEngine::RHI::MRHIBuffer* Buffer)
{
  MRHIScoped_SwitchGraphicsPipeline scoped{*this};
  gRHIBackend->RHIUnmapBuffer(*this, Buffer);
}

void* MRHICommandList::AllocMemcpy(const void* Src, IN SIZE_T AllocSize, IN SIZE_T Alignment)
{
  void* allocated = Alloc(AllocSize, Alignment);
  // TODO
  ::memcpy(allocated, Src, AllocSize);
  return allocated;
}

void MRHICommandList::ActivatePipeline(ERHIPipeline NewPipeline)
{
  me_assert(GetPipeline() != NewPipeline);

  m_activatePipeline = NewPipeline;

  // Push a command to cmdList
  auto activatePipelineCommand = 
  [
    Pipeline = NewPipeline
  ]
  (MRHICommandList& CmdList)
  {

    IRHIGraphicsContext*& context = CmdList.m_graphicContext;

    switch (Pipeline)
    {
      case ERHIPipeline::Graphics:
      {
        context = gRHIBackend->GetDefaultGraphicsContext();
      };
      break;

      case ERHIPipeline::None:
      {
        // Reset the context
        context = nullptr;
      }
    }
  };

  PushLambda(std::move(activatePipelineCommand));
}

void* MRHICommandList::Alloc(IN SIZE_T AllocSize, IN SIZE_T Alignment)
{
  return m_memoryManager.Allocate(AllocSize, Alignment);
}

void MRHIGraphicsCommandList::DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum)
{
  if (ShouldExecuteImmediatly())
  {
    GetGraphicContextChecked().DrawPrimitive(StartVertexIndex, PrimitiveNum, InstanceNum);
  }
  else
  {
    (void)AllocCommandAndConstruct<MEngine::RHI::MRHIDrawPrimitiveCommand>(StartVertexIndex, PrimitiveNum, InstanceNum);
  }
}

void MRHIGraphicsCommandList::SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO)
{
  if (ShouldExecuteImmediatly())
  {
    GetGraphicContextChecked().SetGraphicsPipelineState(GraphicsPSO);
  }
  else
  {
    (void)AllocCommandAndConstruct<MEngine::RHI::MRHISetGraphicsPSOCommand>(GraphicsPSO);
  }
}

void MRHIGraphicsCommandList::SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding)
{
  if (ShouldExecuteImmediatly())
  {
    GetGraphicContextChecked().SetVertexBufferBinding(BindingSlotIndex, VertexBuffer, VertexBinding);
  }
  else
  {
    (void)AllocCommandAndConstruct<MEngine::RHI::MRHISetVertexBufferBindingCommand>(BindingSlotIndex, VertexBuffer, VertexBinding);
  }
}

void MRHIGraphicsCommandList::StartDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport)
{
  if (ShouldExecuteImmediatly())
  {
    GetGraphicContextChecked().StartDrawingViewport(Viewport);
  }
  else
  {
    (void)AllocCommandAndConstruct<MEngine::RHI::MRHIStartDrawingViewportCommand>(Viewport);
  }
}

void MRHIGraphicsCommandList::EndDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport)
{
  if (ShouldExecuteImmediatly())
  {
    GetGraphicContextChecked().EndDrawingViewport(Viewport);
  }
  else
  {
    (void)AllocCommandAndConstruct<MEngine::RHI::MRHIEndDrawingViewportCommand>(Viewport);
  }
}

void MRHIGraphicsCommandList::Test_DrawTriangle()
{
  gRHIBackend->RHITest_DrawTriangle();
}

} // namespace MEngine::RHI

} // namespace MEngine