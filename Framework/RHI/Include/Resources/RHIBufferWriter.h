#pragma once

#ifndef _ME_RHI_BUFFERWRITER_
#define _ME_RHI_BUFFERWRITER_

#include "RHIDefines.h"
#include "RHIFwd.h"
#include "Resources/RHIBuffers.h"
#include <functional>

namespace MEngine
{

namespace RHI
{

class MRHIBufferWriter
{  

public:
  // NOTE: typedef makes cpp unable to reconize it. An error in msvc maybe? So we use using(c++11) 
  using WriterFinalizer = std::function<RHIBufferRefPtr(MEngine::RHI::MRHICommandList&)>;

  RHI_API static const MRHIBufferWriter InvalidWriter;

  RHI_API MRHIBufferWriter(IN MRHICommandList* InCmdList, IN MRHIBuffer* InBuffer, IN void* InDest, IN SIZE_T InDestSize, IN WriterFinalizer&& InFinalizer);

  RHI_API ~MRHIBufferWriter();

  RHI_API RHIBufferRefPtr Finalize();

  private:
    WriterFinalizer Finalizer = nullptr;

    MRHICommandList* CommandList;

    MRHIBuffer* Buffer;

    void* Destination;

    SIZE_T DestSize;
};

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_BUFFERWRITER_