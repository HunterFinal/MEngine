#include "APP_Generic/GenericPlatformApplicationAccessPort.h"
#include "Null/NullApplication.h"
#include "Null/NullPlatformGlobals.h"

#include <memory>

namespace
{
  std::shared_ptr<MEngine::Application::MNullApplication> gNullApplication{nullptr};  
}

namespace MEngine
{
  namespace Application
  {
    
    std::shared_ptr<MAbstractApplication> MGenericPlatformApplicationAccessPort::CreateApplication()
    {
      if (gNullApplication == nullptr)
      {
        gNullApplication = MNullApplication::CreateNullApplication();
      }

      return gNullApplication;
    } 

    void MGenericPlatformApplicationAccessPort::TerminateApplication(DEFAULT_VAR bool bForceTerminate)
    {
      // TODO should extend it with variable bForceTerminate
      // May not release global null application because it is shared
      gNullApplication.reset();
    }
  }
}