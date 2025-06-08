#include "Null/NullApplicationEventHandler.h"

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
  }
}