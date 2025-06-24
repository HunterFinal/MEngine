#pragma once

#ifndef _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_
#define _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_

#include "Misc/CoreDefines.h"
#include "Definitions/CoreDefinitions.h"

#include <memory>

namespace MEngine
{
  namespace Application
  {
    class MAbstractApplicationWindow;
  }
}

using MEngine::Application::MAbstractApplicationWindow;

namespace MEngine
{
  namespace FutureFlex
  {
    class FFWindow : public std::enable_shared_from_this<FFWindow>
    {
      public:

        FUTUREFLEXCORE_API FFWindow();
        FUTUREFLEXCORE_API ~FFWindow();

        FUTUREFLEXCORE_API void ShowWindow();
        FUTUREFLEXCORE_API void HideWindow();
        FUTUREFLEXCORE_API void RequestDestroyWindow();
        FUTUREFLEXCORE_API void ForceDestroyWindow();
        FUTUREFLEXCORE_API void SetNativeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& NativeWindow);
        FUTUREFLEXCORE_API std::shared_ptr<MAbstractApplicationWindow> GetNativeWindow();
        FUTUREFLEXCORE_API std::shared_ptr<const MAbstractApplicationWindow> GetNativeWindow() const;
        
      private:
        std::shared_ptr<MAbstractApplicationWindow> m_nativeWindowPtr;
        bool m_bIsShown;
    };
  }
}

#endif // _ME_RUNTIME_FUTUREFLEX_CORE_FFWINDOWS_