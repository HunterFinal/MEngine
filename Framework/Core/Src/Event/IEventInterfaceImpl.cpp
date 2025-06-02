#include "Event/IEventInterface.h"
#include "Templates/TypeCast.h"

namespace MEngine
{
  namespace Core
  {
    std::string IEventInterface::ToString() const
    { 
      return std::string(GetName());
    }
    bool IEventInterface::IsCategory(IN EEventCategory Category) const
    {
      return (EnumCast(GetEventCategory()) & EnumCast(Category)) != 0;
    }
  }
}