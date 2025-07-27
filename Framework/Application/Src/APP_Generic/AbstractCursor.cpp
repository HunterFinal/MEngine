#include "APP_Generic/AbstractCursor.h"

namespace MEngine
{
  namespace Application
  {
    MAbstractCursor::MAbstractCursor()
      : CurtCursorType(ECursorType::None)
    { }

    MAbstractCursor::~MAbstractCursor() = default;
  }
}