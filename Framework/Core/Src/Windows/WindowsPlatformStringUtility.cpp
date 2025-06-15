#include "Windows/WindowsPlatformStringUtility.h"

#include <cstdarg>
#include <cstdio>
// strlen usage
#include <cstring>
#include <cwchar>

namespace
{
  /**
   * Convert result of vsnprintf and vswprintf to -1 if overflow occurs
   */
  int32 ValidateSPrintfResult(IN const int32 Result, IN const int32 BufferSize);
}

namespace MEngine
{
  namespace Core
  {
    SIZE_T MWindowsPlatformStringUtility::Strlen(IN const ANSICHAR* Str)
    {
      return static_cast<SIZE_T>(::strlen(Str));
    }

    SIZE_T MWindowsPlatformStringUtility::Strlen(IN const WIDECHAR* Str)
    {
      return static_cast<SIZE_T>(::wcslen(Str));
    }

    SIZE_T MWindowsPlatformStringUtility::Strlen(IN const UTF8CHAR* Str)
    {
      return Strlen(reinterpret_cast<const ANSICHAR*>(Str));
    }

    WIDECHAR* MWindowsPlatformStringUtility::Strcpy(
      OUT WIDECHAR* Dest, 
      IN const WIDECHAR* Src, 
      IN const SIZE_T DestCount
    )
    {
      if ((Dest == nullptr) || (Src == nullptr))
      {
        return nullptr;
      }

      return static_cast<WIDECHAR*>(wcsncpy(Dest, Src, DestCount));
    }

    int32 MWindowsPlatformStringUtility::PrintBufferV(
      IN WIDECHAR* BufferAddress,
      IN const SIZE_T BufferSize,
      IN const WIDECHAR* Format,
      IN va_list Args)
    {
      const int32 writtenResultCnt = vswprintf(BufferAddress, BufferSize, Format, Args);
      return ValidateSPrintfResult(writtenResultCnt, static_cast<int32>(BufferSize));
    }

    int32 MWindowsPlatformStringUtility::PrintBufferV(
      IN ANSICHAR* BufferAddress,
      IN const SIZE_T BufferSize,
      IN const ANSICHAR* Format,
      IN va_list Args)
    {
      const int32 writtenResultCnt = vsnprintf(BufferAddress, BufferSize, Format, Args);
      return ValidateSPrintfResult(writtenResultCnt, static_cast<int32>(BufferSize));
    }
  }
}

namespace
{
  int32 ValidateSPrintfResult(
    IN const int32 Result, 
    IN const int32 BufferSize
  )
  {
    return ((Result != -1) && (Result < BufferSize)) ? Result : -1;
  }
}