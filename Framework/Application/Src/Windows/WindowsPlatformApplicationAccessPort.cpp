#include "Windows/WindowsPlatformApplicationAccessPort.h"
#include "Windows/WindowsPlatformApplication.h"
#include "Windows/WindowsPlatformGlobals.h"

#include "Windows/WindowsHeaderSet.h"

// Icon resource
#include "Windows/Resources/resource.h"

namespace
{
  // Real MWindowsPlatformApplication instance pointer
  std::shared_ptr<MEngine::Application::MWindowsPlatformApplication> gWindowsApplication{nullptr};
}

namespace MEngine
{
  namespace Application
  {
    std::shared_ptr<MAbstractApplication> MWindowsPlatformApplicationAccessPort::CreateApplication()
    {
      if (gWindowsApplication == nullptr)
      {
        HICON appIconHandle = ::LoadIcon(gHInstance, MAKEINTRESOURCE(GetApplicationIcon()));
        if (appIconHandle == nullptr)
        {
          appIconHandle = ::LoadIcon(static_cast<HINSTANCE>(nullptr), IDI_APPLICATION);
        }

        gWindowsApplication = MWindowsPlatformApplication::CreateWindowsApplication(gHInstance, appIconHandle);
      }

      return gWindowsApplication;
    }

    void MWindowsPlatformApplicationAccessPort::TerminateApplication(DEFAULT_VAR bool bForceTerminate)
    {
      // FIXME Temporary code
      (void)bForceTerminate;
      // TODO should extend it with variable bForceTerminate
      // May not release global null application because it is shared
      gWindowsApplication.reset();
    }

    int32 MWindowsPlatformApplicationAccessPort::GetApplicationIcon()
    {
      return ID_ICON_MENGINE;
    }
  }
}