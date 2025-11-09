#pragma once

#ifndef _ME_RUNTIME_FUTUREFLEXCORE_FFWIDGET_
#define _ME_RUNTIME_FUTUREFLEXCORE_FFWIDGET_

#include <memory>

namespace MEngine
{

namespace FutureFlex
{

  /**
   * @brief Base class for FutureFlex widgets
   * 
   */
  class FFWidget : public std::enable_shared_from_this<FFWidget>
  {
    
  };

} // namespace MEngine::FutureFlex

} // namespace MEngine

#endif // _ME_RUNTIME_FUTUREFLEXCORE_FFWIDGET_