#include "FutureFlexCore/Application/FutureFlexApplication.h"

#include "HAL/PlatformApplicationAccessPort.h"
#include "APP_Generic/AbstractApplication.h"
#include "Macro/AssertionMacros.h"

namespace MEngine
{
  namespace FutureFlex
  {
    std::shared_ptr<MFutureFlexApplication> MFutureFlexApplication::s_curtAppInstance = nullptr;
    std::shared_ptr<MAbstractApplication> MFutureFlexApplication::s_platformApp = nullptr;

    MFutureFlexApplication::~MFutureFlexApplication()
    {

    }

    void MFutureFlexApplication::Initialize()
    {
      Initialize(MPlatformApplicationAccessPort::CreateApplication());
    }

    void MFutureFlexApplication::Initialize(IN const std::shared_ptr<MAbstractApplication>& PlatformApplication)
    {
      me_assert(PlatformApplication != nullptr);

      s_platformApp = PlatformApplication;
      s_curtAppInstance = std::shared_ptr<MFutureFlexApplication>(new MFutureFlexApplication());

      s_platformApp->SetEventHandler(std::dynamic_pointer_cast<MApplicationEventHandler>(s_curtAppInstance));

    }

    bool MFutureFlexApplication::IsInitialized()
    {
      return s_curtAppInstance != nullptr;
    }

    MFutureFlexApplication& MFutureFlexApplication::GetInstance()
    {
      me_assert(IsInitialized());

      return *s_curtAppInstance.get();
    }

    void MFutureFlexApplication::Update()
    {

    }

    bool MFutureFlexApplication::OnKeyDown()
    {
      return false;
    }
    bool MFutureFlexApplication::OnKeyUp()
    {
      return false;
    }
    bool MFutureFlexApplication::OnMouseDown()
    {
      return false;
    }
    bool MFutureFlexApplication::OnMouseUp()
    {
      return false;
    }
    bool MFutureFlexApplication::OnMouseMove()
    {
      return false;
    }

    MFutureFlexApplication::MFutureFlexApplication()  
    {}

    void MFutureFlexApplication::OnTerminateFFApp()
    {
      
    }

  }
}