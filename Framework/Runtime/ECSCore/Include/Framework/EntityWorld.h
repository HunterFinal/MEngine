#pragma once

#ifndef _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYWORLD_
#define _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYWORLD_

#include "Framework/Entity.h"
#include "Framework/Fwd.h"

#include <vector>

namespace MEngine
{

namespace ECSCore
{
  /**
   * @brief Core class to manage all entities and components
   */
  class MEntityWorld final
  {
    private:
      std::vector<MEntity<>> a;
  };
}  

}

#endif // _ME_RUNTIME_ECSCORE_FRAMEWORK_ENTITYWORLD_