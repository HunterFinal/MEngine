#pragma once

#ifndef _ME_CORE_MODULES_DYNAMICMODULEMANIFEST_
#define _ME_CORE_MODULES_DYNAMICMODULEMANIFEST_

#include "CoreDefines.h"

#include <unordered_map>
#include <string>

namespace MEngine
{

namespace Core
{

struct MModuleManifest
{
  std::unordered_map<std::wstring, std::wstring> ModuleNameFilenameTable;

  CORE_API MModuleManifest();

  static CORE_API std::wstring GetFilename(IN const std::wstring& DirectoryPath);
  
  static CORE_API bool ReadManifest(IN const std::wstring& Filename, OUT MModuleManifest& OutManifest);

};

} // namespace MEngine::Module

} // namespace MEngine


#endif // _ME_CORE_MODULES_DYNAMICMODULEMANIFEST_