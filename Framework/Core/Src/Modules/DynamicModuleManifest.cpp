#include "Modules/DynamicModuleManifest.h"

#include "HAL/PlatformStringUtility.h"
#include "Utils/FileHelper.h"

#include "ManifestParser.h"

// TODO Move this to CMake
#define CMAKE_MODULE_MANIFEST MTEXT("ModuleManifest.manifest")

namespace
{
  void AppendOrUpdateManifest(OUT MEngine::Core::MModuleManifest& OutManifest, IN const std::wstring& ModuleName, IN const std::wstring& ModulePath);
}

namespace MEngine
{

namespace Core
{

  MModuleManifest::MModuleManifest() = default;

  std::wstring MModuleManifest::GetFilename(IN const std::wstring& DirectoryPath)
  {
    return DirectoryPath + CMAKE_MODULE_MANIFEST;
  }
  
  bool MModuleManifest::ReadManifest(IN const std::wstring& Filename, OUT MModuleManifest& OutManifest)
  {
    std::wstring fileStr{};
    if (!MFileHelper::ReadFileToString(Filename.c_str(), fileStr))
    {
      return false;
    }

    const TCHAR* strPtr = fileStr.data();
    // Start parsing data in file
    (void)MManifestParser::ConsumeWhiteSpace(strPtr);

    // We will finish reading manifest if the first character is not '{' or
    // immediately finish with '}' (Empty manifest) 
    if (!MManifestParser::TryConsumeChar(strPtr, MTEXT('{')) || !MManifestParser::ConsumeWhiteSpace(strPtr) || MManifestParser::TryConsumeChar(strPtr, MTEXT('}')))
    {
      return false;
    }

    while (true)
    {
      // Remove the white space for property field name parsing
      (void)MManifestParser::ConsumeWhiteSpace(strPtr);
      std::wstring propertyField{};
      propertyField.reserve(64);
      // Read the property field name
      if (!MManifestParser::ParseString(strPtr, propertyField))
      {
        return false;
      }

      (void)MManifestParser::ConsumeWhiteSpace(strPtr);
      // There should have a ':' after property field.
      if (!MManifestParser::TryConsumeChar(strPtr, MTEXT(':')))
      {
        return false;
      }
      (void)MManifestParser::ConsumeWhiteSpace(strPtr);

      // Try to figure out property field
      if (MPlatformStringUtility::Strcmp(propertyField.c_str(), MTEXT("Modules")) == 0)
      {
        // Load all properties inside "Modules"'s field
        (void)MManifestParser::ConsumeWhiteSpace(strPtr);
        if (!MManifestParser::TryConsumeChar(strPtr, MTEXT('{')))
        {
          return false;
        }
        (void)MManifestParser::ConsumeWhiteSpace(strPtr);

        // Stop parsing if data inside "Modules"'s field is empty
        if (!MManifestParser::TryConsumeChar(strPtr, MTEXT('}')))
        {
          while (true)
          {
            std::wstring moduleName{};
            std::wstring modulePath{};
            moduleName.reserve(64);
            modulePath.reserve(80);
            
            (void)MManifestParser::ConsumeWhiteSpace(strPtr);
            // Parse module name and module path 
            // Example: "ModuleName": "ModulePath" is correct.(independent of the count of white space) 
            if (!MManifestParser::ParseString(strPtr, moduleName)   ||
                !MManifestParser::ConsumeWhiteSpace(strPtr)         ||
                !MManifestParser::TryConsumeChar(strPtr, MTEXT(':'))||
                !MManifestParser::ConsumeWhiteSpace(strPtr)         ||
                !MManifestParser::ParseString(strPtr, modulePath)
              )
              {
                return false;
              }

            AppendOrUpdateManifest(OutManifest, moduleName, modulePath); 

            (void)MManifestParser::ConsumeWhiteSpace(strPtr);

            // Stop parsing if we reach the end
            if (MManifestParser::TryConsumeChar(strPtr, MTEXT('}')))
            {
              break;
            }

            // Datas are connected by ',' so we should check
            if (!MManifestParser::TryConsumeChar(strPtr, MTEXT(',')))
            {
              return false;
            }
          }
        }
      }
      // Expected name of property field 
      else
      {
        return false;
      }

      (void)MManifestParser::ConsumeWhiteSpace(strPtr);

      if (MManifestParser::TryConsumeChar(strPtr, MTEXT('}')))
      {
        // We reach the end of manifest here
        return true;
      }

      if (!MManifestParser::TryConsumeChar(strPtr, MTEXT(',')))
      {
        // There are another property fields left but not connected by ','
        return false;
      }
    }
  }

} // namespace MEngine::Core

} // namespace MEngine

namespace
{
  void AppendOrUpdateManifest(OUT MEngine::Core::MModuleManifest& OutManifest, IN const std::wstring& ModuleName, IN const std::wstring& ModulePath)
  {
    if (OutManifest.ModuleNameFilenameTable.contains(ModuleName))
    {
      OutManifest.ModuleNameFilenameTable[ModuleName] = ModulePath;
    }
    else
    {
      OutManifest.ModuleNameFilenameTable.emplace(ModuleName, ModulePath);
    }
  }
}

#undef CMAKE_MODULE_MANIFEST