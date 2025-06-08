#include "Windows/WindowsPlatformApplicationInstance.h"
#include "Windows/WindowsHeaderSet.h"

namespace MEngine
{
  namespace Application
  {
    MWindowsPlatformApplicationInstance::MWindowsPlatformApplicationInstance(IN HINSTANCE InstanceHandle)
      : m_instance(reinterpret_cast<MApplicationInstanceInternal*>(InstanceHandle))
    { }

    MWindowsPlatformApplicationInstance::MWindowsPlatformApplicationInstance(MWindowsPlatformApplicationInstance&& Other) noexcept
      : m_instance(std::move(Other.m_instance))
    { }

    MWindowsPlatformApplicationInstance& MWindowsPlatformApplicationInstance::operator=(MWindowsPlatformApplicationInstance&& Other) noexcept
    {
      if (this != &Other)
      {
        m_instance = Other.m_instance;
        Other.m_instance = nullptr;
      }

      return *this;
    }

    bool MWindowsPlatformApplicationInstance::IsValid() const
    {
      // TODO maybe from another progress
      // TODO need manage all HINSTANCE
      return m_instance != nullptr;
    }

    HINSTANCE MWindowsPlatformApplicationInstance::GetInstance() const
    {
      return reinterpret_cast<HINSTANCE>(m_instance);
    }

    MWindowsPlatformApplicationInstance::operator bool() const noexcept
    {
      return IsValid();
    }

    MWindowsPlatformApplicationInstance::operator HINSTANCE() const noexcept
    {
      return GetInstance();
    }
  }
}