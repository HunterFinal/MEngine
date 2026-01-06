#pragma once

#ifndef _ME_CORE_MODULES_MANIFESTPARSER_
#define _ME_CORE_MODULES_MANIFESTPARSER_

#include "CoreDefines.h"
#include <string>

struct MManifestParser
{
  static bool TryConsumeChar(OUT const TCHAR*& OutPtr, IN TCHAR Ch);
  static bool ConsumeWhiteSpace(OUT const TCHAR*& OutPtr);
  static bool ParseString(OUT const TCHAR*& OutPtr, OUT std::wstring& OutStr);
  
  private:
    ~MManifestParser() = delete;
};

#endif // _ME_CORE_MODULES_MANIFESTPARSER_