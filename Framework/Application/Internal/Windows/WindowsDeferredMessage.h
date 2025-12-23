#pragma once

#ifndef _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_
#define _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_

#include "Windows/WindowsHeaderSet.h"
#include "Windows/WindowsPlatformWindow.h"

#include <memory>

namespace MEngine
{

namespace Application
{
  class MWindowsPlatformWindow;

  // Windows deferred message structure
  struct MWindowsDeferredMessage
  {
    std::weak_ptr<MWindowsPlatformWindow> NativeWindowWeakPtr;
    HWND HWnd;
    uint32 Message;
    WPARAM WParam;
    LPARAM LParam;
    int32 MouseX;
    int32 MouseY;
    int32 MouseIndicatorFlags;
  };

} // namespace MEngine::Application

} // namespace MEngine


#endif // _ME_APPLICATION_INTERNAL_WINDOWS_DEFERRED_MESSAGE_