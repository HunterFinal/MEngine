#include "Windows/WindowsPlatformStringUtility.h"

// strlen useage
#include <cstring>

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
  }
}