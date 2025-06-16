#pragma once

#ifndef _ME_APPLICATION_WINDOWS_PLATFORM_CURSOR_
#define _ME_APPLICATION_WINDOWS_PLATFORM_CURSOR_

#include "APP_Generic/AbstractCursor.h"

namespace MEngine
{
  namespace Application
  {
    class MWindowsPlatformCursor : public MAbstractCursor
    {
      public:
        MWindowsPlatformCursor();
          
        /**Start of MAbstractCursor interface */
        #pragma region MAbstractCursor interface
        virtual ~MWindowsPlatformCursor() = default;
        virtual Vector2 GetPosition() const override;
        virtual void SetPosition(IN const int32 X, IN const int32 Y) override;
        virtual void Show() override;
        virtual void Hide() override;
        virtual void LockInRect(IN const MCursorRect& Rect) override;
        virtual void Unlock() override;
        #pragma endregion MAbstractCursor interface
        /**End of MAbstractCursor interface */

      private:
    };
  }
}

#endif // _ME_APPLICATION_WINDOWS_PLATFORM_CURSOR_