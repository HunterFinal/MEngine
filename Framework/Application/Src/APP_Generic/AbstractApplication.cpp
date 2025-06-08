#include "APP_Generic/AbstractApplication.h"
#include "Internal/Factories/ApplicationEventHandlerFactory.h"
#include "Null/NullApplicationEventHandler.h"

namespace MEngine
{
  namespace Application
  {
    MAbstractApplication::MAbstractApplication()
      : m_eventHandler{std::static_pointer_cast<MApplicationEventHandler>(MApplicationEventHandlerFactory::CreateNullEventHandler())}
    { }

    void MAbstractApplication::SetEventHandler(const std::shared_ptr<MApplicationEventHandler>& EventHandler)
    {
      m_eventHandler.reset();
      m_eventHandler = EventHandler;
    }

    std::shared_ptr<MApplicationEventHandler> MAbstractApplication::GetEventHandler() const
    {
      return m_eventHandler;
    }
  }
}