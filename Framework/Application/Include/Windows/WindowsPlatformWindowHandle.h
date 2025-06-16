#pragma once

#ifndef _ME_APP_WINDOWS_PLATFORM_WINDOW_HANDLE_
#define _ME_APP_WINDOWS_PLATFORM_WINDOW_HANDLE_

#include "ApplicationAPI.h"

struct HWND__;
using HWND = HWND__*;

namespace MEngine
{
  namespace Application
  {
    class MWindowsPlatformWindowHandle final
    {
      class MWindowHandleInternal
      {
        int m_memoryPlaceHolder_Unused = 0;
      };

      public:
        APP_API explicit MWindowsPlatformWindowHandle(IN HWND WindowHandle);
        APP_API ~MWindowsPlatformWindowHandle() = default;

        APP_API MWindowsPlatformWindowHandle(IN const MWindowsPlatformWindowHandle& Other);
        APP_API MWindowsPlatformWindowHandle& operator=(IN const MWindowsPlatformWindowHandle& Other);
        APP_API MWindowsPlatformWindowHandle(IN MWindowsPlatformWindowHandle&& Other) noexcept;
        APP_API MWindowsPlatformWindowHandle& operator=(IN MWindowsPlatformWindowHandle&& Other) noexcept;
        
        APP_API bool IsValid() const;
        APP_API HWND GetHandle() const;
        APP_API operator HWND() const noexcept;
        APP_API explicit operator bool() const noexcept;

      private:
        MWindowHandleInternal* m_handle;
    };
  }
}

TYPEDEF(MEngine::Application::MWindowsPlatformWindowHandle, WindowHandle);

// Equality comparation
APP_API bool operator==(const WindowHandle& Lhs, const WindowHandle& Rhs);
APP_API bool operator!=(const WindowHandle& Lhs, const WindowHandle& Rhs);

#endif // _ME_APP_WINDOWS_PLATFORM_WINDOW_HANDLE_