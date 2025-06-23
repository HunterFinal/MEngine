#include "KeyInputInfoContainerBuilder.h"
#include "Containers/KeyInputInfoContainer.h"

namespace MEngine
{
  namespace Application
  {
    // TODO Fake const
    MKeyInputInfoContainer MKeyInputInfoContainerBuilder::Build() const
    {
      MKeyInputInfoContainer product = 
                                     {
                                       .ActualKeyCode = m_keyCode,
                                       .CharacterCode = m_characterCode,
                                       .RepeatCount = m_repeatCount,
                                       .bIsRepeat = m_bIsRepeat 
                                     };

      const_cast<MKeyInputInfoContainerBuilder*>(this)->ResetBuilder();
      return product;
    }

    void MKeyInputInfoContainerBuilder::ResetBuilder()
    {
      m_keyCode = 0;
      m_characterCode = 0;
      m_repeatCount = 0;
      m_bIsRepeat = false;
    }
  }
}
