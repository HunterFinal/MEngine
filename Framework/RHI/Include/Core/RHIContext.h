#pragma once

#ifndef _ME_RHI_CORE_RHICONTEXT_
#define _ME_RHI_CORE_RHICONTEXT_

#include "HAL/Platform.h"
#include "RHIDefines.h"

namespace MEngine
{

namespace RHI
{
  /**
   * IRHIGraphicsContext
   * 
   * This interface represents a graphics-only rendering context in RHI layer
   * 
   * // TODO Need more description
   * 
   */
  class IRHIGraphicsContext
  {
    public:
      RHI_API ~IRHIGraphicsContext() = default;

      virtual void RHIDrawPrimitiveShape(IN uint32 StartVertexIndex, IN uint32 PrimitiveNum, IN uint32 InstanceNum) = 0;
  };
}

}


#endif // _ME_RHI_CORE_RHICONTEXT_