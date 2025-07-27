#include "Null/NullApplication.h"

#include "Null/NullApplicationWindow.h"
#include "Null/NullPlatformCursor.h"

namespace MEngine
{
namespace Application
{
  std::shared_ptr<MNullApplication> MNullApplication::CreateNullApplication()
  {
    return std::shared_ptr<MNullApplication>(new MNullApplication());
  }

  void MNullApplication::PeekMessages()
  {
    // Empty implementation
  }

  void MNullApplication::UpdateApplication(IN const float DeltaTime)
  {
    // Empty implementation
    (void)DeltaTime;
  }
  
  void MNullApplication::ProcessDeferredMessages()
  {
    // Empty implementation
  }
  std::shared_ptr<MAbstractApplicationWindow> MNullApplication::CreateApplicationWindow()
  {
    return MNullApplicationWindow::CreateNullWindow();
  }
  void MNullApplication::InitializeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& Window,
                                          IN const MWindowDefinition& WindowDefinition,
                                          IN const std::shared_ptr<MAbstractApplicationWindow>& ParentWindow)
  {
    const std::shared_ptr<MNullApplicationWindow> nullWindow = std::dynamic_pointer_cast<MNullApplicationWindow>(Window);
    const std::shared_ptr<MNullApplicationWindow> nullParentWindow = std::dynamic_pointer_cast<MNullApplicationWindow>(ParentWindow);

    nullWindow->InitializeNullWindow(shared_from_this(), WindowDefinition, nullParentWindow);
    m_windows.emplace_back(nullWindow);
  }

  void MNullApplication::TerminateApplication()
  {

  }

  MNullApplication::MNullApplication()
    : Super(std::make_shared<MNullPlatformCursor>())
    , m_windows{}
  {
    // Empty implementation
    // TODO need implementation
  }
}
}