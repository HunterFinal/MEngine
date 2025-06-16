#include "Windows/WindowsPlatformCursor.h"
#include "Windows/WindowsHeaderSet.h"

#include "Macro/AssertionMacros.h"
#include "Math/Vector2D.h"
#include "Templates/TypeCast.h"

namespace
{
  constexpr int32 gNativeCursorCount = EnumCast(MEngine::Application::ECursorType::CursorCount);
  HCURSOR gNativeCursorHandles[gNativeCursorCount];

  HCURSOR GetNativeCursorHandle(IN const MEngine::Application::ECursorType Type);
}

namespace MEngine
{
  namespace Application
  {
    MWindowsPlatformCursor::MWindowsPlatformCursor()
      : m_customCursor{}
    {
      for (int32 nativeCursorIndex = 0; nativeCursorIndex < gNativeCursorCount; ++nativeCursorIndex)
      {
        gNativeCursorHandles[nativeCursorIndex] = NULL;

        ECursorType curtCursorIndexType = static_cast<ECursorType>(nativeCursorIndex);
        
        HCURSOR curtCursorHandle = GetNativeCursorHandle(curtCursorIndexType);
        
        gNativeCursorHandles[nativeCursorIndex] = curtCursorHandle;
      }

      SetType(ECursorType::Default);
    }

    MWindowsPlatformCursor::~MWindowsPlatformCursor()
    {
      // TODO
      // Release custom cursor
      // Native cursors will automatically be destoryed when application is destroyed
      // use DestroyCursor to release custom cursor
      for (size_t customCursorIndex = 0; customCursorIndex < m_customCursor.size(); ++customCursorIndex)
      {
        HCURSOR customCursor = m_customCursor[customCursorIndex];
        ::DestroyCursor(customCursor);
      }
    }

    Vector2 MWindowsPlatformCursor::GetPosition() const
    {
      POINT cursorPos{};
      ::GetCursorPos(&cursorPos);

      return Vector2{static_cast<double>(cursorPos.x), static_cast<double>(cursorPos.y)};
    }

    void MWindowsPlatformCursor::SetPosition(IN const int32 X, IN const int32 Y)
    {
      ::SetCursorPos(X, Y);
    }

    void MWindowsPlatformCursor::Show()
    {
      // ShowCursor(true) actually increments an internal value.
      // Keep calling it to make sure cursor shows
      // URL https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-showcursor
      while(::ShowCursor(true) < 0);
    }

    void MWindowsPlatformCursor::Hide()
    {
      // ShowCursor(false) actually decrements an internal value.
      // Keep calling it to make sure cursor hides
      // URL https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-showcursor
      while(::ShowCursor(false) >= 0);
    }

    void MWindowsPlatformCursor::LockInRect(IN const MCursorRect& Rect)
    {
      RECT lockRect = {
        .left = Rect.Left,
        .top = Rect.Top,
        .right = Rect.Right,
        .bottom = Rect.Bottom
      };
      ::ClipCursor(&lockRect);
    }

    void MWindowsPlatformCursor::Unlock()
    {
      ::ClipCursor(nullptr);
    }

    void MWindowsPlatformCursor::SetTypeImpl(IN const ECursorType Type)
    {
      // Assert if Type is greater than MEngine::Application::ECursorType::CursorCount
      me_assert((EnumCast(Type) < gNativeCursorCount));

      ::SetCursor(gNativeCursorHandles[EnumCast(Type)]);
    }
  }
}

namespace
{
  HCURSOR GetNativeCursorHandle(IN const MEngine::Application::ECursorType Type)
  {
    using enum MEngine::Application::ECursorType;
    HCURSOR cursorHandle = NULL;

    switch(Type)
    {
      case None:
      {

      }
      break;

      case Default:
      {
        cursorHandle = ::LoadCursor(nullptr, IDC_ARROW);
      }
      break;

      default:
      {
        // Invalid cursor type
        me_assert(false);
      } 
      break;
    }

    return cursorHandle;
  }
}