#include "Null/NullPlatformCursor.h"
#include "Math/Vector2D.h"

namespace MEngine
{

namespace Application
{
  MNullPlatformCursor::MNullPlatformCursor()
    : m_positionX(0)
    , m_positionY(0)
  { }
  
  MNullPlatformCursor::~MNullPlatformCursor() = default;

  Vector2D MNullPlatformCursor::GetPosition() const
  {
    return Vector2D{static_cast<double>(m_positionX), static_cast<double>(m_positionY)};
  }

  void MNullPlatformCursor::SetPosition(IN const int32 X, IN const int32 Y)
  {
    m_positionX = X;
    m_positionY = Y;
  }

  void MNullPlatformCursor::Show()
  {
    // Empty implementation
  }

  void MNullPlatformCursor::Hide()
  {
    // Empty implementation
  }

  void MNullPlatformCursor::LockInRect(IN const MCursorRect& Rect)
  {
    // Empty implementation
  }

  void MNullPlatformCursor::Unlock()
  {
    // Empty implementation
  }

  void MNullPlatformCursor::SetType(IN const ECursorType Type)
  {
    // Empty implementation
  }

} // namespace MEngine::Application

} // namespace MEngine