#pragma once

#ifndef _ME_APP_APPLICATION_EVENT_HANDLER_
#define _ME_APP_APPLICATION_EVENT_HANDLER_

#include "Misc/CoreDefines.h"
#include "Macro/ApplicationDefines.h"
#include "Containers/KeyCharContainer.h"

namespace std
{
  template<typename _Ty>
  class shared_ptr;
}

namespace MEngine
{
  namespace Application
  {
    struct MKeyCharContainer;
    class MAbstractApplicationWindow;

    struct APP_API MApplicationEventHandler
    {
      virtual ~MApplicationEventHandler() = default;
  
      virtual bool OnKeyDown() = 0;

      virtual bool OnKeyUp() = 0;

      virtual bool OnKeyChar(IN const MKeyCharContainer& Container) = 0;

      virtual bool OnMouseDown() = 0;

      virtual bool OnMouseUp() = 0;

      virtual bool OnMouseMove() = 0;

      virtual void OnWindowCreate(IN const std::shared_ptr<MAbstractApplicationWindow>& Window, IN const bool bIsSetFocus) = 0;
      
      virtual void OnWindowClose(IN const std::shared_ptr<MAbstractApplicationWindow>& Window) = 0;
    };
  }
}

#endif // _ME_APP_APPLICATION_EVENT_HANDLER_