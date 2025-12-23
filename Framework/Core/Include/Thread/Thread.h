#pragma once

#ifndef _ME_CORE_THREAD_
#define _ME_CORE_THREAD_

#include "CoreDefines.h"
#include "Macro/AssertionMacros.h"

#include <thread>

namespace MEngine
{

namespace Thread
{

class MThread
{

public:

protected:
  std::thread ThreadObject;
};

} // namespace MEngine::Thread

} // namespace MEngine

#endif // _ME_CORE_THREAD_