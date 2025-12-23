#pragma once

#ifndef _ME_CORE_THREAD_WORKER_
#define _ME_CORE_THREAD_WORKER_

#include "CoreDefines.h"
#include "Macro/AssertionMacros.h"

#include <thread>
#include <utility>


namespace MEngine
{

namespace Thread
{

class MThreadWorker
{
  template<typename FuncType, typename... ArgTypes>
  NODISCARD_CTOR explicit MThreadWorker(IN FuncType&& InThreadFunc, IN ArgTypes&&... args);

  private:
    std::thread m_threadObj;
};

template<typename FuncType, typename... ArgTypes>
MThreadWorker::MThreadWorker(IN FuncType&& InThreadFunc, IN ArgTypes&&... args)
  : m_threadObj(std::forward<FuncType>(InThreadFunc), std::forward<ArgTypes>(args...))
{
  me_assert(InThreadFunc != nullptr);
}


} // namespace MEngine::Thread

} // namespace MEngine

#endif // _ME_CORE_THREAD_WORKER_