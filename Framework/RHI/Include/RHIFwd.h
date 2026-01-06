#pragma once

#ifndef _ME_RHI_FWD_
#define _ME_RHI_FWD_

#include "CoreDefines.h"
#include "RHIConcepts.h"

namespace MEngine
{

namespace RHI
{

class  IRHIGraphicsContext;
class  MRHIResource;
class  MRHIBuffer;
class  MRHIBufferWriter;
class  MRHICommandList;
struct MRHIBufferDescriptor;

template<typename RefType>
Requires_Derived_From(RefType, MEngine::RHI::MRHIResource)
class TRHIRefCountPtr;

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_FWD_