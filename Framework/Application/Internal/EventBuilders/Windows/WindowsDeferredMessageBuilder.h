#pragma once

#ifndef _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_BUILDER_
#define _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_BUILDER_

#include "Misc/CoreDefines.h"
#include "Macro/ApplicationDefines.h"

#include "Windows/WindowsHeaderSet.h"
#include "Windows/WindowsPlatformWindow.h"
#include <memory>

namespace MEngine
{

namespace Application
{
  struct MWindowsDeferredMessage;

  struct MWindowsDeferredMessageBuilder final
  {
    TYPEDEF(MWindowsDeferredMessageBuilder&, ThisBuilder);

    public:
      static MWindowsDeferredMessageBuilder& Builder()
      {
        static MWindowsDeferredMessageBuilder Builder;
        return Builder;
      }

      APP_API MWindowsDeferredMessage Build() const;
      APP_API void Reset();
      ~MWindowsDeferredMessageBuilder() = default;

      ThisBuilder NativeWindow(IN const std::shared_ptr<MWindowsPlatformWindow>& NativeWindow)
      {
        m_nativeWindow = NativeWindow;
        return *this;
      }

      ThisBuilder WindowHandle(IN const HWND HWnd)
      {
        m_hwnd = HWnd;
        return *this;
      }

      ThisBuilder Message(IN const uint32 Message)
      {
        m_message = Message;
        return *this;
      }

      ThisBuilder WParam(IN const WPARAM WParam)
      {
        m_WParam = WParam;
        return *this;
      }

      ThisBuilder LParam(IN const LPARAM LParam)
      {
        m_LParam = LParam;
        return *this;
      }

      ThisBuilder MouseX(IN const int32 MouseX)
      {
        m_mouseX = MouseX;
        return *this;
      }

      ThisBuilder MouseY(IN const int32 MouseY)
      {
        m_mouseY = MouseY;
        return *this;
      }

      ThisBuilder MouseIndicatorFlags(IN const int32 MouseIndicatorFlags)
      {
        m_mouseIndicatorFlags = MouseIndicatorFlags;
        return *this;
      }

    private:
      std::weak_ptr<MWindowsPlatformWindow> m_nativeWindow;
      HWND m_hwnd;
      uint32 m_message;
      WPARAM m_WParam;
      LPARAM m_LParam;
      int32 m_mouseX;
      int32 m_mouseY;
      int32 m_mouseIndicatorFlags;
  };
  
} // namespace MEngine::Application

} // namespace MEngine

#endif // _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_BUILDER_