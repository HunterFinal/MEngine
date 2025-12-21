#pragma once

#ifndef _ME_RHI_CORE_RHIBACKEND_
#define _ME_RHI_CORE_RHIBACKEND_

#include "RHIDefines.h"

namespace MEngine
{

namespace RHI
{
  /**
   * IRHIBackend
   * 
   * The interface which represents the active Rendering Hardware Interface backend.
   *
   * This class abstracts the underlying graphics API implementation
   * (e.g. OpenGL, Vulkan, DirectX 12)
   *
   * RHIBackend is NOT a GPU device in the strict API sense.
   * - For Vulkan / DX12, it typically wraps a VkDevice / ID3D12Device.
   * - For OpenGL, it represents the currently active graphics context
   *   and its associated global state.
   */
  class IRHIBackend
  {
    public:
      RHI_API virtual ~IRHIBackend() = default;

      /**Initialize the RHI backend */
      virtual void Initialize() = 0;

      /**Called after the IRHIBackend::Initialize */
      virtual void PostInitialize() {}

      /**Shutdown the RHI backend. Handle internal state cleanup and resource destruction before the actual destructor is called  */
      virtual void Shutdown() = 0;
  };

} // namespace MEngine::RHI

} // namespace MEngine


#endif // _ME_RHI_CORE_RHIBACKEND_