#pragma once

#ifndef _ME_APP_APPLICATION_EVENT_HANDLER_
#define _ME_APP_APPLICATION_EVENT_HANDLER_

namespace MEngine
{
  namespace Application
  {
    struct MApplicationEventHandler
    {
      public:
        virtual ~MApplicationEventHandler() = default;
    
        virtual bool OnKeyDown() = 0;
        virtual bool OnKeyUp() = 0;
        virtual bool OnMouseDown() = 0;
        virtual bool OnMouseUp() = 0;
        virtual bool OnMouseMove() = 0;
    };
  }
}

#endif // _ME_APP_APPLICATION_EVENT_HANDLER_