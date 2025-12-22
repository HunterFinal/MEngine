#pragma once

#ifndef _ME_RHI_INTERNAL_WINDOWSRHIPLATFORM_
#define _ME_RHI_INTERNAL_WINDOWSRHIPLATFORM_

#include "RHIDefines.h"
#include "Macro/TypeAliasMacro.h"
#include "Misc/CoreDefines.h"

namespace MEngine
{

namespace RHI
{
  /**前方宣言 */
  class IRHIBackend;

  struct MWindowsRHIPlatform
  {
    static IRHIBackend* CreateRHIBackend();

    static void ShutdownRHIBackend(IN IRHIBackend* RHIBackend);
  };

} // namespace MEngine::RHI

} // namespace MEngine

TYPEDEF(MEngine::RHI::MWindowsRHIPlatform, RHIPlatform);

#endif // _ME_RHI_INTERNAL_WINDOWSRHIPLATFORM_