#pragma once

#ifndef _ME_APPLICATION_NULL_PLATFORM_CURSOR_
#define _ME_APPLICATION_NULL_PLATFORM_CURSOR_

#include "App_Generic/AbstractCursor.h"

namespace MEngine
{

namespace Application
{
  class MNullPlatformCursor : public MAbstractCursor
  { 
    public:
      MNullPlatformCursor();
      virtual ~MNullPlatformCursor();

      /**Start MAbstractCursor interface */
      #pragma region MAbstractCursor interface
        virtual Vector2D GetPosition() const override;
        virtual void SetPosition(IN const int32 X, IN const int32 Y) override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void LockInRect(IN const MCursorRect& Rect) override;
        virtual void Unlock() override;
        virtual void SetType(IN const ECursorType Type) override;
      #pragma endregion MAbstractCursor interface
      /**End MAbstractCursor interface */

    private:
      int32 m_positionX;
      int32 m_positionY;
  };
} // namespace MEngine::Application

} // namespace MEngine

#endif // _ME_APPLICATION_NULL_PLATFORM_CURSOR_