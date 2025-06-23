#include "Widgets/FFWindow.h"

#include "Application/FutureFlexApplication.h"

#include "APP_Generic/AbstractApplicationWindow.h"

namespace MEngine
{
  namespace FutureFlex 
  {
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