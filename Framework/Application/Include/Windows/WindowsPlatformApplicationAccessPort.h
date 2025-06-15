#pragma once

#ifndef _ME_APP_WINDOWS_PLATFORM_APPLICATION_ACCESS_PORT_
#define _ME_APP_WINDOWS_PLATFORM_APPLICATION_ACCESS_PORT_

#include "APP_Generic/GenericPlatformApplicationAccessPort.h"
#include "Macro/TypeAliasMacro.h"

namespace MEngine
{
  namespace Application
  {
    struct MWindowsPlatformApplicationAccessPort : public MGenericPlatformApplicationAccessPort
    {
      APP_API static std::shared_ptr<MAbstractApplication> CreateApplication();
      APP_API static void TerminateApplication(DEFAULT_VAR bool bForceTerminate = false);
      APP_API static int32 GetApplicationIcon();

      MWindowsPlatformApplicationAccessPort() = delete;
      ~MWindowsPlatformApplicationAccessPort() = delete;
    };
  }
}

TYPEDEF(MEngine::Application::MWindowsPlatformApplicationAccessPort, MPlatformApplicationAccessPort);

#endif // _ME_APP_WINDOWS_PLATFORM_APPLICATION_ACCESS_PORT_