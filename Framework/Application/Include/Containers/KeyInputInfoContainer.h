#pragma once

#ifndef _ME_APPLICATION_KEY_INPUT_INFO_CONTAINER_
#define _ME_APPLICATION_KEY_INPUT_INFO_CONTAINER_

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Application
  {
    struct MKeyInputInfoContainer
    {
      uint32 ActualKeyCode;
      uint32 CharacterCode;
      uint16 RepeatCount;
      bool bIsRepeat;
    };
  }
}

#endif // _ME_APPLICATION_KEY_INPUT_INFO_CONTAINER_