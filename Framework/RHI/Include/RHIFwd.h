#pragma once

#ifndef _ME_RHI_FWD_
#define _ME_RHI_FWD_

#include "RHIConcepts.h"

namespace MEngine
{

namespace RHI
{

class  IRHIGraphicsContext;
class  MRHICommandList;

struct MRHIVertexElement;
struct MRHIVertexBinding;

class  MRHIResource;
class  MRHIBuffer;
class  MRHIShader;
class  MRHIVertexInputLayout;
class  MRHIGraphicsPipelineState;
class  MRHIViewport;

struct MRHIBufferDescriptor;
struct MRHIVertexBindingDescriptor;
class  MRHIBufferWriter;

template<typename RefType>
Requires_Derived_From(RefType, MEngine::RHI::MRHIResource)
class TRHIRefCountPtr;

} // namespace MEngine::RHI

} // namespace MEngine

#endif // _ME_RHI_FWD_