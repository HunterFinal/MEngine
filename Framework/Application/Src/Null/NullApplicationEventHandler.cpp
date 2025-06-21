#include "Null/NullApplicationEventHandler.h"
#include "Containers/KeyCharContainer.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    MNullApplicationEventHandler::~MNullApplicationEventHandler()
    { }

    bool MNullApplicationEventHandler::OnKeyDown()
    {
      return false;
    }

    bool MNullApplicationEventHandler::OnKeyUp()
    {
      return false;
    }

    bool MNullApplicationEventHandler::OnKeyChar(IN const MKeyCharContainer& Container)
    {
      (void)Container;
      return false;
    }

    bool MNullApplicationEventHandler::OnMouseDown()
    {
      return false;
    }

    bool MNullApplicationEventHandler::OnMouseUp()
    {
      return false;
    }

    bool MNullApplicationEventHandler::OnMouseMove()
    {
      return false;
    }

    void MNullApplicationEventHandler::OnWindowCreate(
      IN const std::shared_ptr<MAbstractApplicationWindow>& Window, 
      IN const bool bIsSetFocus)
    {
      // Ignore unuse warning
      (void)Window;
      (void)bIsSetFocus;
    }
    void MNullApplicationEventHandler::OnWindowClose(IN const std::shared_ptr<MAbstractApplicationWindow>& Window)
    {
      // Ignore unuse warning
      (void)Window;
    }
  }
}