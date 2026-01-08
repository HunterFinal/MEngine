#pragma once

#ifndef _ME_RHI_FWD_
#define _ME_RHI_FWD_

#include "RHIConcepts.h"

namespace MEngine
{

namespace RHI
{

class  IRHIGraphicsContext;

class  MRHIResource;
class  MRHIBuffer;
class  MRHIShader;
class  MRHIVertexShader;

struct MRHIBufferDescriptor;
class  MRHIBufferWriter;
class  MRHICommandList;

template<typename RefType>
Requires_Derived_From(RefType, MEngine::RHI::MRHIResource)
class TRHIRefCountPtr;

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_FWD_