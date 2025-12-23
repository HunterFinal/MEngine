#pragma once

#ifndef _ME_APPLICATION_GENERIC_PLATFORM_APPLICATION_ACCESS_PORT_
#define _ME_APPLICATION_GENERIC_PLATFORM_APPLICATION_ACCESS_PORT_

#include "CoreDefines.h"
#include "Macro/ApplicationDefines.h"

namespace std
{
  template<typename _Ty>
  class shared_ptr;
}

namespace MEngine
{
  namespace Application
  {
    class MAbstractApplication;
    struct MKeyCharContainer;

    struct MGenericPlatformApplicationAccessPort
    {
      APP_API static std::shared_ptr<MAbstractApplication> CreateApplication();
      /**
       * // TODO This is dangerous if caller use it without expectation
       */
      APP_API static void TerminateApplication(DEFAULT_VAR bool bForceTerminate = false);

      explicit MGenericPlatformApplicationAccessPort() = delete;
      ~MGenericPlatformApplicationAccessPort() = delete;
    };
  }
}

#endif // _ME_APPLICATION_GENERIC_PLATFORM_APPLICATION_ACCESS_PORT_