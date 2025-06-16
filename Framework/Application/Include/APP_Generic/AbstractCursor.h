#pragma once

#ifndef _ME_APPLICATION_ABSTRACT_CURSOR_
#define _ME_APPLICATION_ABSTRACT_CURSOR_

#include "Misc/CoreDefines.h"
#include "Math/MathForward.h"

namespace MEngine
{
  namespace Application
  {
    enum class ECursorType : int32
    {
      /**No cursor to be visible */
      None = 0,

      /**Default arrow cursor */
      Default,

      /**Total count of cursor type */
      CursorCount
    };

    struct MCursorRect
    {
      int32 Left;
      int32 Top;
      int32 Right;
      int32 Bottom;
    };

    struct MCursorHandle
    {
      ECursorType Type;
      TCHAR CursorName[256]; 
    };

    class MAbstractCursor
    {
      public:
        MAbstractCursor();
        
        virtual ~MAbstractCursor() = default;

        virtual Vector2 GetPosition() const = 0;

        virtual void SetPosition(IN const int32 X, IN const int32 Y) = 0;

        virtual void Show() = 0;

        virtual void Hide() = 0;

        virtual void LockInRect(IN const MCursorRect& Rect) = 0;
        
        virtual void Unlock() = 0;

        void SetType(IN const ECursorType Type);

        ECursorType GetType() const;

      private:
        virtual void SetTypeImpl(IN const ECursorType Type) = 0;

      private:
        ECursorType m_curtCursorType;
    };
  };
}

#endif // _ME_APPLICATION_ABSTRACT_CURSOR_