#include "Null/NullApplicationWindow.h"

namespace MEngine
{
  namespace Application
  {
    std::shared_ptr<MNullApplicationWindow> MNullApplicationWindow::CreateNullWindow()
    {
      return std::shared_ptr<MNullApplicationWindow>(new MNullApplicationWindow);
    }

    MNullApplicationWindow::~MNullApplicationWindow()
    { 
      // Empty implementation
    }

    void MNullApplicationWindow::InitializeNullWindow(IN const std::shared_ptr<MNullApplication>& Application,
                                                      IN const MWindowDefinition& WindowDefinition,
                                                      IN const std::shared_ptr<MNullApplicationWindow>& ParentWindow)
    {
      m_applicationInstance = Application;
      m_definition = WindowDefinition;
      (void)ParentWindow;
    }

    /**Start of MAbstractWindow interface implementation */
    #pragma region MAbstractWindow interface implementation
    void MNullApplicationWindow::Destroy()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::ResizeWindow(IN int32 NewX, IN int32 NewY, IN uint32 NewWidth, IN uint32 NewHeight)
    {
      // Empty implementation
      (void)NewX;
      (void)NewY;
      (void)NewWidth;
      (void)NewHeight;
    }
    void MNullApplicationWindow::MoveTo(IN int32 X, IN int32 Y)
    {
      // Empty implementation
      (void)X;
      (void)Y;
    }
    void MNullApplicationWindow::Show()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::Hide()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::Maximize()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::Minimize()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::Enable()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::Disable()
    {
      // Empty implementation
    }
    void MNullApplicationWindow::SetTitle(IN const ANSICHAR* Text)
    {
      // Empty implementation
      (void)Text;
    }
    void MNullApplicationWindow::SetWindowMode(IN EWindowMode NewWindowMode)
    {
      // Empty implementation
      (void)NewWindowMode;
    }
    bool MNullApplicationWindow::IsMaximized() const
    {
      return true;
    }
    bool MNullApplicationWindow::IsMinimized() const
    {
      // Null window would never be minimized
      return false;
    }
    #pragma endregion MAbstractWindow interface implementation
    /**End of MAbstractWindow interface implementation */

    MNullApplicationWindow::MNullApplicationWindow()
      : m_applicationInstance{}
    {
      // Empty implementation
    }
  }
}