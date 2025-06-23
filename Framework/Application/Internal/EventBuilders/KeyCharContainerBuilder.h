#pragma once

#ifndef _ME_APPLICATION_INTERNAL_KEYCHAR_CONTAINER_BUILDER_
#define _ME_APPLICATION_INTERNAL_KEYCHAR_CONTAINER_BUILDER_

#include "Misc/CoreDefines.h"
#include "Macro/ApplicationDefines.h"

namespace MEngine
{
  namespace Application
  {
    struct MKeyCharContainer;

    class MKeyCharContainerBuilder final
    {
      public:
        static MKeyCharContainerBuilder& GetInstance()
        {
          static MKeyCharContainerBuilder Builder;
          return Builder;
        }
        APP_API MKeyCharContainer Build() const;
        APP_API void ResetBuilder();
        ~MKeyCharContainerBuilder() = default;
      
        MKeyCharContainerBuilder& RepeatCount(IN const uint16 RepeatCount)
        {
          m_repeatCount = RepeatCount;
          return *this;
        }
        MKeyCharContainerBuilder& Character(IN const TCHAR Character)
        {
          m_character = Character;
          return *this;
        }
        MKeyCharContainerBuilder& CharacterCode(IN const uint32 CharacterCode)
        {
          m_characterCode = CharacterCode;
          return *this;
        }
        MKeyCharContainerBuilder& AltDownFlag(IN const bool bIsAltDown)
        {
          m_bIsAltDown = bIsAltDown;
          return *this;
        }
        MKeyCharContainerBuilder& KeyRepeatFlag(IN const bool bIsRepeat)
        {
          m_bIsRepeat = bIsRepeat;
          return *this;
        }
        MKeyCharContainerBuilder& KeyUpFlag(IN const bool bIsKeyUp)
        {
          m_bIsKeyUp = bIsKeyUp;
          return *this;
        }
      
      private:
        MKeyCharContainerBuilder()
        { 
          ResetBuilder();
        }

      private:
        uint32 m_characterCode;
        uint16 m_repeatCount;
        TCHAR m_character;
        bool m_bIsAltDown;
        bool m_bIsRepeat;
        bool m_bIsKeyUp;
    };
  }
}

#endif // _ME_APPLICATION_INTERNAL_KEYCHAR_CONTAINER_BUILDER_