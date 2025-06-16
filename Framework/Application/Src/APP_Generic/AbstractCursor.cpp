#include "APP_Generic/AbstractCursor.h"

namespace MEngine
{
  namespace Application
  {
    MAbstractCursor::MAbstractCursor()
      : m_curtCursorType(ECursorType::None)
    { }
    
    void MAbstractCursor::SetType(IN const ECursorType Type)
    {
      m_curtCursorType = Type;

      SetTypeImpl(Type);
    }

    ECursorType MAbstractCursor::GetType() const
    {
      return m_curtCursorType;
    }
  }
}