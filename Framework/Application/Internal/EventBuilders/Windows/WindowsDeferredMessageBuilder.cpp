#include "WindowsDeferredMessageBuilder.h"
#include "Internal/Windows/WindowsDeferredMessage.h"

namespace MEngine
{

namespace Application
{
  MWindowsDeferredMessage MWindowsDeferredMessageBuilder::Build() const
  {
    MWindowsDeferredMessage product =
    {
      .NativeWindowWeakPtr = m_nativeWindow,
      .HWnd = m_hwnd,
      .Message = m_message,
      .WParam = m_WParam,
      .LParam = m_LParam,
      .MouseX = m_mouseX,
      .MouseY = m_mouseY,
      .MouseIndicatorFlags = m_mouseIndicatorFlags
    };

    const_cast<MWindowsDeferredMessageBuilder*>(this)->Reset();
    return product;
  }

  void MWindowsDeferredMessageBuilder::Reset()
  {
    m_nativeWindow.reset();
    m_hwnd = NULL;
    m_message = 0;
    m_WParam = 0;
    m_LParam = 0;
    m_mouseX = 0;
    m_mouseY = 0;
    m_mouseIndicatorFlags = 0;
  }
} // namespace MEngine::Application

} // namespace MEngine