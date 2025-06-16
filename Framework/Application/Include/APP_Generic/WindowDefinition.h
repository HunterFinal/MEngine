#pragma once

#ifndef _ME_APP_WINDOW_DEFINITION_
#define _ME_APP_WINDOW_DEFINITION_

#include <string>

namespace MEngine
{
  namespace Application
  {
    struct MWindowDefinition
    {
      float DesiredPositionOnScreenX;
      float DesiredPositionOnScreenY;
      float DesiredWidthOnScreen;
      float DesiredHeightOnScreen;

      // TODO maybe string
      std::wstring Title;
    };
  }
}

#endif // _ME_APP_WINDOW_DEFINITION_