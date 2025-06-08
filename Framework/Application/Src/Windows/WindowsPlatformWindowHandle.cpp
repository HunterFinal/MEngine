#include "Windows/WindowsPlatformWindowHandle.h"
#include "Windows/WindowsHeaderSet.h"

namespace MEngine
{
  namespace Application
  {
    MWindowsPlatformWindowHandle::MWindowsPlatformWindowHandle(IN HWND WindowHandle)
      : m_handle(reinterpret_cast<MWindowHandleInternal*>(WindowHandle))
    { }

    MWindowsPlatformWindowHandle::MWindowsPlatformWindowHandle(const MWindowsPlatformWindowHandle& Other)
      : m_handle(Other.m_handle)
    { }

    MWindowsPlatformWindowHandle& MWindowsPlatformWindowHandle::operator=(const MWindowsPlatformWindowHandle& Other)
    {
      if (this != &Other)
      {
        m_handle = Other.m_handle;
      }

      return *this;
    }

    MWindowsPlatformWindowHandle::MWindowsPlatformWindowHandle(MWindowsPlatformWindowHandle&& Other) noexcept
      : m_handle(std::move(Other.m_handle))
    { }

    MWindowsPlatformWindowHandle& MWindowsPlatformWindowHandle::operator=(MWindowsPlatformWindowHandle&& Other) noexcept
    {
      if (this != &Other)
      {
        m_handle = Other.m_handle;
        Other.m_handle = nullptr;
      }

      return *this;
    }

    bool MWindowsPlatformWindowHandle::IsValid() const
    {
      return ::IsWindow((HWND)m_handle);
    }

    HWND MWindowsPlatformWindowHandle::GetHandle() const
    {
      return reinterpret_cast<HWND>(m_handle);
    }

    MWindowsPlatformWindowHandle::operator bool() const noexcept
    {
      return IsValid();
    }

    MWindowsPlatformWindowHandle::operator HWND() const noexcept
    {
      return GetHandle();
    }
  }
}