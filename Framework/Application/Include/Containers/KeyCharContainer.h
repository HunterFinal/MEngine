#pragma once

#ifndef _ME_APPLICATION_KEYCHAR_CONTAINER_
#define _ME_APPLICATION_KEYCHAR_CONTAINER_

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Application
  {
    struct MKeyCharContainer
    {
      uint32 CharacterCode;
      uint16 RepeatCount;
      TCHAR Character;
      bool bIsAltDown;
      bool bIsRepeat;
      bool bIsKeyUp;
    };

  }
}

#endif // _ME_APPLICATION_KEYCHAR_CONTAINER_