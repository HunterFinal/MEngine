#include "APP_Generic/AbstractApplication.h"
#include "APP_Generic/AbstractCursor.h"
#include "Null/NullApplicationEventHandler.h"

#include "Internal/Factories/ApplicationEventHandlerFactory.h"

namespace MEngine
{
  namespace Application
  {
    MAbstractApplication::MAbstractApplication(IN const std::shared_ptr<MAbstractCursor>& Cursor)
      : m_eventHandler{std::static_pointer_cast<MApplicationEventHandler>(MApplicationEventHandlerFactory::CreateNullEventHandler())}
      , m_cursor(Cursor)
    { }

    MAbstractApplication::~MAbstractApplication() = default;

    void MAbstractApplication::SetEventHandler(const std::shared_ptr<MApplicationEventHandler>& EventHandler)
    {
      m_eventHandler.reset();
      m_eventHandler = EventHandler;
    }
  }
}