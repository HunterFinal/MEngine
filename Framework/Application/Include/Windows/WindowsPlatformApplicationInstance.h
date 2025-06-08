#pragma once

#ifndef _ME_APP_WINDOWS_PLATFORM_APPLICATION_INSTANCE_
#define _ME_APP_WINDOWS_PLATFORM_APPLICATION_INSTANCE_

#include "ApplicationAPI.h"
#include "Misc/NonCopyable.h"

struct HINSTANCE__;
using HINSTANCE = HINSTANCE__*;

namespace MEngine
{
  namespace Application
  {
    class MWindowsPlatformApplicationInstance final : public MNonCopyable
    {
      class MApplicationInstanceInternal
      {
        int m_memoryPlaceHolder_Unused = 0;
      };

      public:
        APP_API explicit MWindowsPlatformApplicationInstance(IN HINSTANCE ApplicationInstance);
        APP_API ~MWindowsPlatformApplicationInstance() = default;
        
        APP_API bool IsValid() const;
        APP_API HINSTANCE GetInstance() const;
        APP_API operator HINSTANCE() const noexcept;
        APP_API explicit operator bool() const noexcept;

        APP_API MWindowsPlatformApplicationInstance(IN MWindowsPlatformApplicationInstance&& Other) noexcept;
        APP_API MWindowsPlatformApplicationInstance& operator=(IN MWindowsPlatformApplicationInstance&& Other) noexcept;

      private:
        MApplicationInstanceInternal* m_instance;
    };

    TYPEDEF(MWindowsPlatformApplicationInstance, ApplicationInstance);
  }
}

#endif // _ME_APP_WINDOWS_PLATFORM_APPLICATION_INSTANCE_