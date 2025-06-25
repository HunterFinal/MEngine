#include "Globals/CoreGlobals.h"

namespace MEngine
{
  namespace Core
  {
    namespace Globals
    {
      bool GIsRequestApplicationExit = false;
      bool GIsPeekingMessagesOutsideOfMainLoop = false;

      // FIXME Change implementation immediatly
      void RequestApplicationExit()
      {
        // FIXME
        GIsRequestApplicationExit = true;
      }
    }
  }
}