#pragma once

#ifndef _ME_INPUTCORE_INPUT_KEY_TYPES_
#define _ME_INPUTCORE_INPUT_KEY_TYPES_

#include "CoreDefines.h"

namespace MEngine
{

namespace InputCore
{

  enum class EPairedAxisType : uint8
  {
    Unpaired, // This key is Unpaired
    X,        // This key represents the X axis of its PairedAxisKey
    Y,        // This key represents the Y axis of its PairedAxisKey
  };

}

}

#endif // _ME_INPUTCORE_INPUT_KEY_TYPES_