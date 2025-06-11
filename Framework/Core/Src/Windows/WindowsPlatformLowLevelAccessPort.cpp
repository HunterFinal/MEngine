#include "Windows/WindowsPlatformLowLevelAccessPort.h"
#include "Misc/CoreDefines.h"

// Application dll
#include "Windows/WindowsHeaderSet.h"

namespace MEngine
{
  namespace Core
  {
    void MWindowsPlatformLowLevelAccessPort::OutputToLocalDevice(const TCHAR* Str)
    {
      #if ME_DEBUG_LOGGING
        OutputDebugString(Str);
      #endif
    }
  }
}