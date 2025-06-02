#pragma once

#ifndef _ME_WINDOW_EVENT_INSTANCE_IMPL_
#define _ME_WINDOW_EVENT_INSTANCE_IMPL_

#include "Event/IEventInstanceInterface.h"
#include "Delegates/Delegate.h"

namespace MEngine
{
  namespace Core
  {
    class MWindowResizeEventInstance final : public IEventInstanceInterface<MWindowResizeEventInstance>
    {
      friend struct IEventInstanceInterface<MWindowResizeEventInstance>;

      public:
        CORE_API explicit MWindowResizeEventInstance();
        CORE_API ~MWindowResizeEventInstance();

        /**Start of IEventInterface interface */
        EVENT_TYPE_DECLARATION(WindowResize);
        EVENT_CATEGORY_DECLARATION(WindowEvent);
        /**End of IEventInterface interface */
        
      private:
        /**Start CRTP of IEventInstanceInterface */
        CORE_API void Invoke(IN uint32 Width, IN uint32 Height);
        /**End CRTP of IEventInstanceInterface */
      public:
        MAction<void(uint32, uint32)> ResizeEvent;
    };

  }
}

#endif // _ME_WINDOW_EVENT_INSTANCE_IMPL_