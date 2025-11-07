#pragma once

#ifndef _ME_EVENT_INTERFACE_
#define _ME_EVENT_INTERFACE_

#include "Macro/BitOperationMacros.h"
#include "Misc/CoreDefines.h"

#include <string>

#define EVENT_TYPE_DECLARATION(EventType) \
        static EEventType StaticEventType() { return EEventType::##EventType; } \
        virtual EEventType GetEventType() const override { return StaticEventType(); } \
        virtual const ANSICHAR* GetName() const override { return #EventType; }

#define EVENT_CATEGORY_DECLARATION(EventCategory) \
        static EEventCategory StaticEventCategory() { return EEventCategory::##EventCategory; } \
        virtual EEventCategory GetEventCategory() const override { return StaticEventCategory(); }

namespace MEngine
{
  namespace Core
  {
    enum struct EEventType
    {
      None = -1,
      KeyPress, KeyRelease, KeyHold,                                        // Key event
      WindowClose, WindowFocus, WindowLostFocus, WindowMove, WindowResize,  // Window event
      MouseMove, MouseButtonPresse, MouseButtonRelease, MouseScroll,        // Mouse event

      EventTypeCnt,
    };

    enum struct EEventCategory
    {
      None = -1,
      KeyboardEvent = BIT_FLAG(0),
      WindowEvent = BIT_FLAG(1),
      MouseEvent = BIT_FLAG(2),
    };

    struct CORE_API IEventInterface
    {
      virtual ~IEventInterface() = default;

      virtual EEventType GetEventType() const = 0;
      virtual EEventCategory GetEventCategory() const = 0;
      virtual const ANSICHAR* GetName() const = 0;
      virtual std::string ToString() const;
      bool IsCategory(IN EEventCategory Category) const;
    };
  }
}

#endif // _ME_EVENT_INTERFACE_