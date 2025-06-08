#pragma once

#ifndef _ME_APP_ABSTRACT_APPLICATION_WINDOW_
#define _ME_APP_ABSTRACT_APPLICATION_WINDOW_

#include "APP_Generic/WindowDefinition.h"
#include "ApplicationAPI.h"
#include "Misc/NonCopyable.h"

namespace MEngine
{
  namespace Application
  {
    enum struct EWindowMode : uint8
    {
      Fullscreen,
      FullscreenWindowed,
      Windowed,

      WindowModeCount,
    };

    class MAbstractApplicationWindow : public MNonCopyable
    {
      public:
        APP_API explicit MAbstractApplicationWindow() = default;
        APP_API virtual ~MAbstractApplicationWindow() = default;
        APP_API virtual void Destroy() = 0;
        APP_API virtual void ResizeWindow(IN int32 NewX, IN int32 NewY, IN uint32 NewWidth, IN uint32 NewHeight) = 0;
        APP_API virtual void MoveTo(IN int32 X, IN int32 Y) = 0;
        APP_API virtual void Show() = 0;
        APP_API virtual void Hide() = 0;
        APP_API virtual void Maximize() = 0;
        APP_API virtual void Minimize() = 0;
        APP_API virtual void Enable() = 0;
        APP_API virtual void Disable() = 0;
        APP_API virtual void SetTitle(IN const char* Text) = 0;
        APP_API virtual void SetWindowMode(IN EWindowMode NewWindowMode) = 0; 

        APP_API virtual bool IsMaximized() const = 0;
        APP_API virtual bool IsMinimized() const = 0;

        APP_API MAbstractApplicationWindow(IN MAbstractApplicationWindow&& Other) noexcept = default;
        APP_API MAbstractApplicationWindow& operator=(IN MAbstractApplicationWindow&& Other) noexcept = default;

      protected:
        MWindowDefinition m_definition;
    };
  }
}

#endif // _ME_APP_ABSTRACT_APPLICATION_WINDOW_