#include "Application/FutureFlexApplication.h"

#include "Widgets/FFWindow.h"
#include "HAL/PlatformApplicationAccessPort.h"
#include "HAL/PlatformMath.h"
#include "APP_Generic/AbstractApplication.h"
#include "APP_Generic/AbstractApplicationWindow.h"
#include "APP_Generic/AbstractCursor.h"
#include "Macro/AssertionMacros.h"

#include "InputCoreAPI.h"

// TODO
#include "Math/Vector2D.h"

// FIXME move it to another file for version compatibility(c++20)
#include <algorithm>
#include <ranges>

// Shorten namespace
using MEngine::FutureFlex::FFWindow;

namespace
{
  std::shared_ptr<FFWindow> FindWindowByPlatformWindow(
    IN const std::vector<std::shared_ptr<FFWindow>>& WindowsToSearch, 
    IN const std::shared_ptr<const MAbstractApplicationWindow>& PlatformWindow
  );

  void RemoveWindowFromContainer(OUT std::vector<std::shared_ptr<FFWindow>>& WindowContainer, IN const std::shared_ptr<FFWindow>& WindowToRemove);
}

namespace MEngine
{
  namespace FutureFlex
  {
    /**Static member initialization */
    std::shared_ptr<MFutureFlexApplication> MFutureFlexApplication::s_curtAppInstance = nullptr;
    std::shared_ptr<MAbstractApplication> MFutureFlexApplication::s_platformApp = nullptr;

    /**Internal data definition */
    struct MFutureFlexApplication::InternalData
    {
      Vector2D PreviousPlatformCursorPosition = Vector2D::ZeroVector;
    };

    namespace Private
    {
      constexpr float TEMP_DesiredPositionOnScreenX = 10.0f;
      constexpr float TEMP_DesiredPositionOnScreenY = 10.0f;
      constexpr float TEMP_DesiredHeightOnScreen = 768.0f;
      constexpr float TEMP_DesiredWidthOnScreen = 1024.0f;
      constexpr const TCHAR* TEMP_WindowTitle = MTEXT("test");
    }

    MFutureFlexApplication::~MFutureFlexApplication()
    { }

    MFutureFlexApplication& MFutureFlexApplication::GetInstance()
    {
      me_assert(IsInitialized());

      return *s_curtAppInstance;
    }

    void MFutureFlexApplication::Initialize()
    {
      Initialize(MPlatformApplicationAccessPort::CreateApplication());
    }

    void MFutureFlexApplication::Initialize(IN const std::shared_ptr<MAbstractApplication>& PlatformApplication)
    {
      me_assert(PlatformApplication != nullptr);

      // Initialize Input key manager
      MEngine::InputCore::IInputKeyManager& inputKeyManager = MEngine::InputCore::IInputKeyManager::GetInstance();
      inputKeyManager.Initialize();

      s_platformApp = PlatformApplication;
      s_curtAppInstance = std::shared_ptr<MFutureFlexApplication>(new MFutureFlexApplication());
      s_platformApp->SetEventHandler(std::dynamic_pointer_cast<MApplicationEventHandler>(s_curtAppInstance));

    }

    bool MFutureFlexApplication::IsInitialized()
    {
      return s_curtAppInstance != nullptr;
    }

    void MFutureFlexApplication::Terminate()
    {

    }

    void MFutureFlexApplication::AddWindow(std::shared_ptr<FFWindow> FutureFlexWindow)
    {
      if (FutureFlexWindow == nullptr)
      {
        return;
      }

      m_relatedWindows.emplace_back(FutureFlexWindow);
      MakeNativeWindow(FutureFlexWindow);

      FutureFlexWindow->ShowWindow();

    }

    void MFutureFlexApplication::Update()
    {
      // TODO
      UpdatePlatform();
    }

    void MFutureFlexApplication::RequestDestroyWindow(IN std::shared_ptr<FFWindow> WindowToDestroy)
    {
      m_relatedWindowDestroyQueue.emplace(WindowToDestroy);

      DestroyAllRequestedWindow();
    }

    void MFutureFlexApplication::AssignExitRequestedDelegate(const MEngine::Core::MDelegate<void()>& OnExitRequestedDelegate)
    {
      m_onExitRequested = OnExitRequestedDelegate;
    }

    bool MFutureFlexApplication::OnKeyDown(IN const MKeyInputInfoContainer& Container)
    {
      (void)Container;
      return false;
    }

    bool MFutureFlexApplication::OnKeyUp(IN const MKeyInputInfoContainer& Container)
    {
      (void)Container;
      return false;
    }

    bool MFutureFlexApplication::OnKeyChar(IN const MKeyCharContainer& Container)
    {
      (void)Container;
      return false;
    }

    bool MFutureFlexApplication::OnMouseDown()
    {
      return false;
    }

    bool MFutureFlexApplication::OnMouseUp()
    {
      return false;
    }

    bool MFutureFlexApplication::OnMouseMove()
    {
      if (s_platformApp == nullptr)
      {
        // FIXME Add debug message
        return false;
      }

      if (s_platformApp->GetCursor() == nullptr)
      {
        // FIXME Add debug message
        return false;
      }

      
      bool result = true;
      const Vector2D curtCursorPos = s_platformApp->GetCursor()->GetPosition();
      
      if (!m_pImplData->PreviousPlatformCursorPosition.Equals(curtCursorPos))
      {
        // NOTE: We need handle Touch Event
        m_pImplData->PreviousPlatformCursorPosition = curtCursorPos;
      }

      MEngine::Application::MModifierKeysState modState = s_platformApp->GetModState();

      return result;
    }

    bool MFutureFlexApplication::OnCursorSet()
    {
      
      // Handled
      return true;
    }

    void MFutureFlexApplication::OnWindowCreate(
      IN const std::shared_ptr<MAbstractApplicationWindow>& PlatformWindow, 
      IN const bool bIsSetFocus
    )
    {
      (void)PlatformWindow;
      (void)bIsSetFocus;
    }

    void MFutureFlexApplication::OnWindowClose(
      IN const std::shared_ptr<MAbstractApplicationWindow>& PlatformWindow
    ) 
    {
      // TODO Adding implementation
      std::shared_ptr<FFWindow> window = FindWindowByPlatformWindow(m_relatedWindows, PlatformWindow);
      if (window == nullptr)
      {
        return;
      }

      window->RequestDestroyWindow();

    }

    MFutureFlexApplication::MFutureFlexApplication()
      : m_onExitRequested{}
      , m_pImplData{std::make_unique<MFutureFlexApplication::InternalData>()}  
    {
      me_assert(m_pImplData != nullptr);
    }

    void MFutureFlexApplication::MakeNativeWindow(IN std::shared_ptr<FFWindow> FutureFlexWindow)
    {
      me_assert(FutureFlexWindow != nullptr);
      if (s_platformApp == nullptr)
      {
        // FIXME Add debug message
        return;
      }
      // create definition
      MEngine::Application::MWindowDefinition def;
      def.DesiredPositionOnScreenX = Private::TEMP_DesiredPositionOnScreenX;
      def.DesiredPositionOnScreenY = Private::TEMP_DesiredPositionOnScreenY;
      def.DesiredHeightOnScreen = Private::TEMP_DesiredHeightOnScreen;
      def.DesiredWidthOnScreen = Private::TEMP_DesiredWidthOnScreen;
      def.Title = Private::TEMP_WindowTitle;

      // Create native window and initialize window to application
      std::shared_ptr<MEngine::Application::MAbstractApplicationWindow> nativeWindow = s_platformApp->CreateApplicationWindow();
      s_platformApp->InitializeWindow(nativeWindow, def, nullptr);

      FutureFlexWindow->SetNativeWindow(nativeWindow);
    }

    void MFutureFlexApplication::UpdatePlatform()
    {
      if (s_platformApp == nullptr)
      {
        // FIXME Add debug message
        return;
      }
      
      s_platformApp->PeekMessages();
      // FIXME Need timer to calculate delta time
      s_platformApp->UpdateApplication(0.0f);
      s_platformApp->ProcessDeferredMessages();
    }

    void MFutureFlexApplication::OnTerminateFFApp()
    {
      // TODO need implementation
    }

    void MFutureFlexApplication::DestroyAllRequestedWindow()
    {
      using Iterator =  decltype(m_relatedWindowDestroyQueue)::iterator;
      for (Iterator destroyQueueItr = m_relatedWindowDestroyQueue.begin(); destroyQueueItr != m_relatedWindowDestroyQueue.end(); ++destroyQueueItr)
      {
        std::shared_ptr<FFWindow> currentWindowToDestroy = (*destroyQueueItr);
        DestroyWindowImpl(currentWindowToDestroy);
      }

      m_relatedWindowDestroyQueue.clear();
    }

    void MFutureFlexApplication::DestroyWindowImpl(IN const std::shared_ptr<FFWindow>& DestroyedWindow)
    {
      DestroyedWindow->ForceDestroyWindow();

      RemoveWindowFromContainer(m_relatedWindows, DestroyedWindow);

      // TODO Add remove implementation
      {

      }

      bool bHasAnyMainlyUseWindows = false;

      for (const auto& window : m_relatedWindows)
      {
        if (window != nullptr)
        {
          bHasAnyMainlyUseWindows = true;
          break;
        }
      }

      if (!bHasAnyMainlyUseWindows)
      {
        if (m_onExitRequested.IsBound())
        {
          m_onExitRequested.Invoke();
        }
      }
    }
  }
}

namespace
{
  std::shared_ptr<FFWindow> FindWindowByPlatformWindow(
    IN const std::vector<std::shared_ptr<FFWindow>>& WindowsToSearch, 
    IN const std::shared_ptr<const MAbstractApplicationWindow>& PlatformWindow
  )
  {
    for (const std::shared_ptr<FFWindow>& window : WindowsToSearch)
    {
      if (window == nullptr)
      {
        continue;
      }

      const std::shared_ptr<const MAbstractApplicationWindow> nativeWindow = window->GetNativeWindow();

      if (nativeWindow == PlatformWindow)
      {
        return window;
      }
    }

    return std::shared_ptr<FFWindow>{nullptr};
  }

  void RemoveWindowFromContainer(
    OUT std::vector<std::shared_ptr<FFWindow>>& WindowContainer, 
    IN const std::shared_ptr<FFWindow>& WindowToRemove
  )
  {
    // FIXME Need move this to another file for version compability
    auto [removeItrBegin, removeItrEnd] = std::ranges::remove(WindowContainer, WindowToRemove);

    // Remove window inside WindowContainer
    WindowContainer.erase(removeItrBegin, WindowContainer.end());
  
  }
}
