#pragma once

#ifndef _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_
#define _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MAbstractWindow;
  }
}

namespace MEngine
{
  namespace FutureFlex
  {
    class FFWindow
    {
      public:
        
      private:
        std::shared_ptr<MEngine::Application::MAbstractWindow> m_nativeWindowPtr;
    };
  }
}

#endif // _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_