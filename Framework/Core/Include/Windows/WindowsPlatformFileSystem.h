#pragma once

#ifndef _ME_CORE_WINDOWS_PLATFORMFILESYSTEM_
#define _ME_CORE_WINDOWS_PLATFORMFILESYSTEM_

#include "CoreDefines.h"
#include "Serialization/SerializerFwd.h"

namespace MEngine
{

namespace Core
{
  struct MWindowsPlatformFileSystem
  {
    static CORE_API MFileReadSerializer* CreateFileReader(IN const TCHAR* Filename);
    static CORE_API MFileWriteSerializer* CreateFileWriter(IN const TCHAR* Filename);
  };

} // namespace MEngine::Core

} // namespace MEngine

TYPEDEF(MEngine::Core::MWindowsPlatformFileSystem, FileSystem);

#endif // _ME_CORE_WINDOWS_PLATFORMFILESYSTEM_