#include "Windows/WindowsPlatformLowLevelAccessPort.h"

// Application dll
#include "Windows/WindowsHeaderSet.h"

namespace MEngine
{
  namespace Core
  {
    void MWindowsPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(const TCHAR* Str)
    {
      #if ME_DEBUG_LOGGING
        OutputDebugString(Str);
      #else
        (void)Str;
      #endif
    }
  }
}