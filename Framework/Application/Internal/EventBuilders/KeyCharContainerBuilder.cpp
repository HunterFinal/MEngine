#include "KeyCharContainerBuilder.h"
#include "Containers/KeyCharContainer.h"

namespace MEngine
{
  namespace Application
  {
    // TODO Fake const
    MKeyCharContainer MKeyCharContainerBuilder::Build() const
    {
      MKeyCharContainer product =
                                  {
                                    .CharacterCode = m_characterCode,
                                    .RepeatCount = m_repeatCount,
                                    .Character = m_character,
                                    .bIsAltDown = m_bIsAltDown,
                                    .bIsRepeat = m_bIsRepeat,
                                    .bIsKeyUp = m_bIsKeyUp
                                  };

      const_cast<MKeyCharContainerBuilder*>(this)->ResetBuilder();
      return product;
    }

    void MKeyCharContainerBuilder::ResetBuilder()
    {
      m_characterCode = 0;
      m_repeatCount = 0;
      m_character = static_cast<TCHAR>(0);
      m_bIsAltDown = false;
      m_bIsRepeat = false;
      m_bIsKeyUp = false;
    }
  }
}