#include "Generic/GenericPlatformLowLevelAccessPort.h"

#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformStringUtility.h"
#include "Macro/AssertionMacros.h"

// TODO maybe use printf later
#include <cstdio>
#include <iostream>

namespace MEngine
{
  namespace Core
  {
    bool MGenericPlatformLowLevelAccessPort::IsDebuggerPresent()
    {
      #if ME_DEBUG_ON
        return true;
      #else
        return false;
      #endif
    }

    void MGenericPlatformLowLevelAccessPort::PlatformPrintDebugString(const TCHAR* Str)
    {
      MPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(Str);
    }

    void MGenericPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(const TCHAR* Str)
    {
      #if ((defined(UNICODE) && UNICODE) || (defined(_UNICODE) && _UNICODE))
        std::wcout << Str;
      #else
        std::cout << Str;
      #endif
    }

    uint32 MGenericPlatformLowLevelAccessPort::GetLastError()
    {
      return 0u;
    }

    void MGenericPlatformLowLevelAccessPort::SetLastError(IN uint32 ErrorCode) 
    { 
      // Empty implementation
      (void)ErrorCode;
    }

    const TCHAR* MGenericPlatformLowLevelAccessPort::ConvertSystemErrorMessage(IN TCHAR* Buffer, IN uint32 BufferSize, IN uint32 ErrorCode)
    {
      const static TCHAR s_errorMessage[] = MTEXT("System error is not available in this platform");
      me_assert(Buffer != nullptr && BufferSize >= SIZE_OF_ARRAY(s_errorMessage));
      (void)ErrorCode;
      MPlatformStringUtility::Strcpy(Buffer, s_errorMessage, static_cast<SIZE_T>(BufferSize));
      return Buffer;
    }
  }
}