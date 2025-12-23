#pragma once

#ifndef _ME_APP_APPLICATION_EVENT_HANDLER_
#define _ME_APP_APPLICATION_EVENT_HANDLER_

#include "CoreDefines.h"
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
    struct MKeyInputInfoContainer;
    class MAbstractApplicationWindow;

    struct APP_API MApplicationEventHandler
    {
      virtual ~MApplicationEventHandler() = default;
  
      virtual bool OnKeyDown(IN const MKeyInputInfoContainer& Container) = 0;

      virtual bool OnKeyUp(IN const MKeyInputInfoContainer& Container) = 0;

      virtual bool OnKeyChar(IN const MKeyCharContainer& Container) = 0;

      virtual bool OnMouseDown() = 0;

      virtual bool OnMouseUp() = 0;

      virtual bool OnMouseMove() = 0;

      virtual bool OnCursorSet() = 0;

      virtual void OnWindowCreate(IN const std::shared_ptr<MAbstractApplicationWindow>& Window, IN const bool bIsSetFocus) = 0;
      
      virtual void OnWindowClose(IN const std::shared_ptr<MAbstractApplicationWindow>& Window) = 0;
    };
  }
}

#endif // _ME_APP_APPLICATION_EVENT_HANDLER_