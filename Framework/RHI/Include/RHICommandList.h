#pragma once

#ifndef _ME_RHI_COMMANDLIST_
#define _ME_RHI_COMMANDLIST_

#include "RHIDefines.h"
#include "Macro/AssertionMacros.h"
#include "Memory/MemoryManagement.h"
#include "RHICommand.h"
#include "RHIContext.h"
#include "RHIPipeline.h"
#include "Resources/RHIBuffers.h"
#include "Utils/RHIRefCountPtr.h"

#include <utility>

namespace MEngine
{

namespace RHI
{

class MRHIBufferWriter;

class MRHICommandList
{

private:
  TYPEDEF(MEngine::Core::MemChunkStack, MRHICommandAllocator);

  friend class MRHICommandIterator;

  struct MRHICommandChain
  {
    IRHICommand* Root  = nullptr;
    IRHICommand** Tail = nullptr;
    SIZE_T CommandNum  = 0;

    MRHICommandChain();
    void PushBack(IN IRHICommand* NewCmd);

    MRHICommandIterator begin();
    MRHICommandIterator end();
  };

public:
  RHI_API MRHICommandList();
  RHI_API virtual ~MRHICommandList();

  template<typename LambdaType>
  Requires_RHICommand_Callable(MRHICommandList, LambdaType)
  void PushLambda(IN LambdaType&& Lambda);

  template<typename CommandType, typename... ConstructArgs>
  Requires_Derived_From(CommandType, MEngine::RHI::IRHICommand)
  CommandType* AllocCommandAndConstruct(ConstructArgs&&... Args);

  RHI_API bool IsRecording() const;

  RHI_API bool IsExecuting() const;

  RHI_API bool IsImmediate() const;

  RHI_API bool ShouldExecuteImmediatly() const;

  RHI_API bool HasAnyCommand() const;

  RHI_API MEngine::RHI::ERHIPipeline GetPipeline() const;

  RHI_API MEngine::RHI::IRHIGraphicsContext& GetGraphicContextChecked();

  RHI_API void ExecuteCommands();

  RHI_API void SwitchPipeline(MEngine::RHI::ERHIPipeline NewPipeline);

  RHI_API MEngine::RHI::MRHIBufferWriter CreateBufferWriter(const MEngine::RHI::MRHIBufferDescriptor& Descriptor);

  RHI_API void* MapBuffer(MEngine::RHI::MRHIBuffer* Buffer, IN uint32 Size, IN uint32 Offset, IN MEngine::RHI::EResourceAccessMode AccessMode);

  RHI_API void UnmapBuffer(MEngine::RHI::MRHIBuffer* Buffer);

  RHI_API void* AllocMemcpy(const void* Src, IN SIZE_T AllocSize, IN SIZE_T Alignment);

protected:
  void ActivatePipeline(MEngine::RHI::ERHIPipeline NewPipeline);

private:
  RHI_API void* AllocCommandInternal(IN SIZE_T AllocSize, IN SIZE_T Alignment);

  RHI_API void* Alloc(IN SIZE_T AllocSize, IN SIZE_T Alignment);

  template<typename CommandType>
  Requires_Derived_From(CommandType, MEngine::RHI::IRHICommand)
  void* AllocCommandInternal();

private:
  MRHICommandChain     m_commandChain;
  MRHICommandAllocator m_memoryManager;

  // Context to send actual command to graphics API
  MEngine::RHI::IRHIGraphicsContext* m_graphicContext;

  // Current pipeline
  MEngine::RHI::ERHIPipeline m_activatePipeline;

  uint8 m_bIsExecuting : 1;
  uint8 m_bIsImmediate : 1;
};

template<typename CommandType, typename... ConstructArgs>
Requires_Derived_From(CommandType, MEngine::RHI::IRHICommand)
CommandType* MRHICommandList::AllocCommandAndConstruct(ConstructArgs&&... Args)
{
  static_assert(sizeof(CommandType) > 0, "Can not use incomplete type in AllocCommandAndConstruct");
  return new ( AllocCommandInternal( sizeof(CommandType), alignof(CommandType ) ) ) CommandType{std::forward<ConstructArgs>(Args)...};
}

template<typename CommandType>
Requires_Derived_From(CommandType, MEngine::RHI::IRHICommand)
void* MRHICommandList::AllocCommandInternal()
{
  return AllocCommandInternal(sizeof(CommandType), alignof(CommandType));
}

template<typename LambdaType>
Requires_RHICommand_Callable(MRHICommandList, LambdaType)
void MRHICommandList::PushLambda(IN LambdaType&& Lambda)
{
  if (ShouldExecuteImmediatly())
  {
    Lambda(*this);
  }
  else
  {
    (void)AllocCommandAndConstruct< MEngine::RHI::MRHILambdaCommand<MRHICommandList, LambdaType> >(std::forward<LambdaType>(Lambda));
  }
}

class MRHIGraphicsCommandList : public MRHICommandList
{

public:
  template<typename LambdaType>
  Requires_RHICommand_Callable(MRHIGraphicsCommandList, LambdaType)
  void PushLambda(IN LambdaType&& Lambda);

  RHI_API void DrawPrimitive(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum);
  RHI_API void DrawPrimitiveIndexed();
  RHI_API void SetGraphicsPipelineState(IN MEngine::RHI::MRHIGraphicsPipelineState* GraphicsPSO);
  RHI_API void SetVertexBufferBinding(IN uint32 BindingSlotIndex, IN MEngine::RHI::MRHIBuffer* VertexBuffer, IN const MEngine::RHI::MRHIVertexBinding& VertexBinding);
  RHI_API void StartDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport);
  RHI_API void EndDrawingViewport(IN MEngine::RHI::MRHIViewport* Viewport);

  // TODO Test code
  RHI_API void Test_DrawTriangle();
};

template<typename LambdaType>
Requires_RHICommand_Callable(MRHIGraphicsCommandList, LambdaType)
void MRHIGraphicsCommandList::PushLambda(IN LambdaType&& Lambda)
{
  if (ShouldExecuteImmediatly())
  {
    Lambda(*this);
  }
  else
  {
    (void)AllocCommandAndConstruct< MEngine::RHI::MRHILambdaCommand< MRHIGraphicsCommandList, LambdaType > >(std::forward<LambdaType>(Lambda));
  }
}


} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_COMMANDLIST_
