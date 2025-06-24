#include "Widgets/FFWindow.h"

#include "Application/FutureFlexApplication.h"

#include "APP_Generic/AbstractApplicationWindow.h"

namespace MEngine
{
  namespace FutureFlex 
  {
    FFWindow::FFWindow()
      : m_nativeWindowPtr{nullptr}
      , m_bIsShown(false)
    {}

    FFWindow::~FFWindow()
    {
    }

    void FFWindow::ShowWindow()
    {
      if (!m_bIsShown)
      {
        if (m_nativeWindowPtr != nullptr)
        {
          m_nativeWindowPtr->Show();
        }
      }
    }

    void FFWindow::HideWindow()
    {
      if (m_bIsShown)
      {
        if (m_nativeWindowPtr != nullptr)
        {
          m_nativeWindowPtr->Hide();
        }
      }
    }

    void FFWindow::RequestDestroyWindow()
    {
      // TODO
      MFutureFlexApplication::GetInstance().RequestDestroyWindow(shared_from_this());
    }

    void FFWindow::ForceDestroyWindow()
    {
      if (m_nativeWindowPtr != nullptr)
      {
        m_nativeWindowPtr->Destroy();
      }
    }

    void FFWindow::SetNativeWindow(IN const std::shared_ptr<MAbstractApplicationWindow>& NativeWindow)
    {
      me_assert(NativeWindow != nullptr);
      m_nativeWindowPtr = NativeWindow;
    }

    std::shared_ptr<MAbstractApplicationWindow> FFWindow::GetNativeWindow()
    {
      return std::const_pointer_cast<MAbstractApplicationWindow>(static_cast<const FFWindow*>(this)->GetNativeWindow());
    }

    std::shared_ptr<const MAbstractApplicationWindow> FFWindow::GetNativeWindow() const
    {
      return m_nativeWindowPtr;
    }
  }
}