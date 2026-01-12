#include "Resources/RHIBufferWriter.h"
#include "Utils/RHIScoped.h"

namespace MEngine
{

namespace RHI
{
  
const MRHIBufferWriter MRHIBufferWriter::InvalidWriter{nullptr, nullptr, nullptr, 0, nullptr};

MRHIBufferWriter::MRHIBufferWriter(IN MRHICommandList* InCmdList, IN MRHIBuffer* InBuffer, IN void* InDest, IN SIZE_T InDestSize, IN WriterFinalizer&& InFinalizer)
  : Finalizer{std::move(InFinalizer)}
  , CommandList{InCmdList}
  , Buffer{InBuffer}
  , Destination{InDest}
  , DestSize{InDestSize}
{
  me_assert((InBuffer != nullptr) && (InCmdList != nullptr));
}

MRHIBufferWriter::~MRHIBufferWriter()
{
  // Ensure to call Finalize before destruction
  me_assert(Finalizer == nullptr);
}

RHIBufferRefPtr MRHIBufferWriter::Finalize()
{
  RHIBufferRefPtr result{nullptr};

  if (Finalizer != nullptr)
  {
    me_assert((Buffer != nullptr) && (CommandList != nullptr));

    MRHIScoped_SwitchGraphicsPipeline scoped{*CommandList};
    result = Finalizer(*CommandList);

    Finalizer = nullptr;
    CommandList = nullptr;
    Buffer = nullptr;
    Destination = nullptr;
    DestSize = 0;
  }

  return result;
}

}

}