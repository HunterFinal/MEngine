#pragma once

#ifndef _ME_CORE_UTILS_FILEHELPER_
#define _ME_CORE_UTILS_FILEHELPER_

#include "CoreDefines.h"

#include <string>

namespace MEngine
{

namespace Core
{
  struct MFileHelper
  {
    static CORE_API bool ReadFileToString(IN const TCHAR* Filename, OUT std::wstring& OutString);
  };

} // namespace MEngine::Core

} // namespace MEngine


#endif // _ME_CORE_UTILS_FILEHELPER_