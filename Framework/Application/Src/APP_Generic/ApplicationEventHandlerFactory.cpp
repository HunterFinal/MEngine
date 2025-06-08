#include "Internal/Factories/ApplicationEventHandlerFactory.h"
#include "Null/NullApplicationEventHandler.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    std::shared_ptr<MNullApplicationEventHandler> MApplicationEventHandlerFactory::CreateNullEventHandler()
    {
      return std::make_shared<MNullApplicationEventHandler>();
    }
  }
}

