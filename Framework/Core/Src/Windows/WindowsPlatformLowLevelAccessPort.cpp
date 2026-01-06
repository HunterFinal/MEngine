#include "Windows/WindowsPlatformLowLevelAccessPort.h"
#include "Macro/AssertionMacros.h"
#include "Windows/WindowsHeaderSet.h"

#include <string>
#include <filesystem>
#include <iostream>


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

    void* MWindowsPlatformLowLevelAccessPort::GetDllLibrary(IN const TCHAR* Filename)
    {
      me_assert(Filename != nullptr);

      // NOTE We assume dll is in the same directory as .exe
      // FIXME Change it in future when dlls is separated to .exe

      // Avoiding windows dialog boxes if missing
      DWORD errorMode = 0;

      errorMode |= SEM_NOOPENFILEERRORBOX;
      errorMode |= SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX;

      DWORD prevErrorMode = 0;
      const BOOL bHavePrevErrorMode = ::SetThreadErrorMode(errorMode, &prevErrorMode);

      // Finally we actual load the module
      // If library is already loaded then just return it's handle
      void* loadedHandle = ::GetModuleHandle(Filename);
      if (loadedHandle != nullptr)
      {
        return loadedHandle;
      }
      
      // Try to load the actual library
      loadedHandle = ::LoadLibrary(Filename);

      // TODO
      if (loadedHandle == nullptr)
      {
        std::cout << "Failed to load Library" << std::endl;
        std::wcout << L"Library path:" << Filename << std::endl;
        std::cout << "GetLastError = " << ::GetLastError() << std::endl;
      }

      if (bHavePrevErrorMode)
      {
        (void)::SetThreadErrorMode(prevErrorMode, NULL);
      }

      return loadedHandle;
    }

    void MWindowsPlatformLowLevelAccessPort::UnloadDllLibrary(IN void* Handle)
    {
      // Ignore result even we pass a nullptr to it
      (void)::FreeLibrary(reinterpret_cast<HMODULE>(Handle));
    }

    const TCHAR* MWindowsPlatformLowLevelAccessPort::GetBaseDir()
    {
      static TCHAR sDirResult[MAX_PATH] = {'\0'};
      // Initialize buffer
      if (sDirResult[0] == 0)
      {
        // Get executable path
        HMODULE curtModule = NULL;
        // Get the path containing the current module if possible, or use the path containing the executable if not

        // First argument declaration:
        // URL:https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandleexa
        const DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
        const BOOL bUseCurtModulePath = ::GetModuleHandleEx(flags, reinterpret_cast<LPCWSTR>(&GetBaseDir), &curtModule);
        // Use path containing the executable
        if (bUseCurtModulePath == 0)
        {
          curtModule = reinterpret_cast<HMODULE>(gHInstance);
        }

        // Get filename and convert to path containing the module(dll or exe)
        ::GetModuleFileName(curtModule, sDirResult, SIZE_OF_ARRAY(sDirResult));

        // Since windows use \ in path, convert all \ to /.
        std::wstring tempResult = std::filesystem::path{sDirResult}.generic_wstring();

        // Copy converted path to result
        // TODO this is not good for cross platform.
        ::wcsncpy_s(sDirResult, tempResult.data(), tempResult.size());

        // Set directory to result
        const SIZE_T resultTailIdx = tempResult.find_last_of(L'/') + 1;
        sDirResult[resultTailIdx] = static_cast<TCHAR>('\0');

      }

      return sDirResult;
    }

    uint32 MWindowsPlatformLowLevelAccessPort::GetLastError()
    {
      return static_cast<uint32>(::GetLastError());
    }

    void MWindowsPlatformLowLevelAccessPort::SetLastError(IN uint32 ErrorCode)
    {
      ::SetLastError(static_cast<DWORD>(ErrorCode));
    }

    const TCHAR* MWindowsPlatformLowLevelAccessPort::ConvertSystemErrorMessage(IN TCHAR* Buffer, IN uint32 BufferSize, IN uint32 ErrorCode)
    {
      me_assert((Buffer != nullptr) && BufferSize > 0);
      if (ErrorCode == ERROR_SUCCESS)
      {
        ErrorCode = GetLastError();
      }

      // Language identifier
      // User default language
      // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/winnt/nf-winnt-makelangid
      // constexpr DWORD LANGUAGE_ID = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
      constexpr DWORD LANGUAGE_ID = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

      // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/winbase/nf-winbase-formatmessage
      (void)::FormatMessage(
                            FORMAT_MESSAGE_FROM_SYSTEM,
                            nullptr,
                            ErrorCode,
                            LANGUAGE_ID,
                            reinterpret_cast<LPWSTR>(Buffer),
                            BufferSize,
                            nullptr
                           );
      
      return Buffer;
    }
  }
}