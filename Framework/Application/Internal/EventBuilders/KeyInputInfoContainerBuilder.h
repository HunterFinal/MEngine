#pragma once

#ifndef _ME_APPLICATION_INTERNAL_KEYINPUT_INFO_CONTAINER_BUILDER_
#define _ME_APPLICATION_INTERNAL_KEYINPUT_INFO_CONTAINER_BUILDER_

#include "CoreDefines.h"
#include "Macro/ApplicationDefines.h"

namespace MEngine
{
  namespace Application
  {
    struct MKeyInputInfoContainer;

    struct MKeyInputInfoContainerBuilder final
    {
      public:
        static MKeyInputInfoContainerBuilder& GetInstance()
        {
          static MKeyInputInfoContainerBuilder Builder;
          return Builder;
        }
        APP_API MKeyInputInfoContainer Build() const;
        APP_API void ResetBuilder();
        ~MKeyInputInfoContainerBuilder() = default;

        MKeyInputInfoContainerBuilder& ActualKeyCode(IN const uint32 KeyCode)
        {
          m_keyCode = KeyCode;
          return *this;
        }

        MKeyInputInfoContainerBuilder& CharacterCode(IN const uint32 CharacterCode)
        {
          m_characterCode = CharacterCode;
          return *this;
        }
      
        MKeyInputInfoContainerBuilder& RepeatCount(IN const uint16 RepeatCount)
        {
          m_repeatCount = RepeatCount;
          return *this;
        }

        MKeyInputInfoContainerBuilder& KeyRepeatFlag(IN const bool bIsRepeat)
        {
          m_bIsRepeat = bIsRepeat;
          return *this;
        }
      
      private:
        MKeyInputInfoContainerBuilder()
        { 
          ResetBuilder();
        }

      private:
        uint32 m_keyCode;
        uint32 m_characterCode;
        uint16 m_repeatCount;
        bool m_bIsRepeat;
    };
  }
}

#endif // _ME_APPLICATION_INTERNAL_KEYINPUT_INFO_CONTAINER_BUILDER_