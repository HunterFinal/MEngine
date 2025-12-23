#pragma once

#ifndef _ME_CORE_GLOBALS
#define _ME_CORE_GLOBALS

#include "CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    namespace Globals
    {
      extern CORE_API bool GIsRequestApplicationExit;
      extern CORE_API bool GIsPeekingMessagesOutsideOfMainLoop;

      FORCEINLINE bool IsApplicationExitRequested()
      {
        return GIsRequestApplicationExit;
      }

      CORE_API void RequestApplicationExit();
    }
  }
}

// TODO
namespace Globals = MEngine::Core::Globals;

#endif // _ME_CORE_GLOBALS