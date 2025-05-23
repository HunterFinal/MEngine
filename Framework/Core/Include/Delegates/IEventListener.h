#pragma once

#ifndef ME_EVENT_LISTENER_INTERFACE
#define ME_EVENT_LISTENER_INTERFACE

// TODO
#include "Misc/CoreDefines.h"
#include "HAL/Platform.h"

namespace MEngine
{
  struct CORE_API IEventListener
  {
    virtual ~IEventListener() = default;
  };
}

#endif// ME_EVENT_LISTENER_INTERFACE