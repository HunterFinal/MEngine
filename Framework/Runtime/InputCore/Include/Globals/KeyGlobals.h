#pragma once

#ifndef _ME_INPUTCORE_GLOBALS_KEYGLOBALS_
#define _ME_INPUTCORE_GLOBALS_KEYGLOBALS_

#include "Internal/Misc/InputCoreDefines.h"
#include "Misc/CoreDefines.h"
#include "Core/InputKey.h"

namespace MEngine
{

namespace InputCore
{
  extern INPUTCORE_API const MInputKey::KeyNameType INVALID_KEY_NAME;
  extern INPUTCORE_API const MInputKey::KeyNameType INVALID_KEY_DISPLAY_NAME;
  extern INPUTCORE_API const MInputKey::KeyNameType INVALID_KEY_CATEGORY;
  extern INPUTCORE_API const MInputKey::KeyNameType NAME_KEYBOARD_CATEGORY;
  extern INPUTCORE_API const MInputKey::KeyNameType NAME_GAMEPAD_CATEGORY;
  extern INPUTCORE_API const MInputKey::KeyNameType NAME_MOUSE_CATEGORY;

  struct GStaticKeys
  {
    static INPUTCORE_API const MInputKey Any;

    // Mouse input keys
    static INPUTCORE_API const MInputKey Mouse_X;
    static INPUTCORE_API const MInputKey Mouse_Y;
    static INPUTCORE_API const MInputKey Mouse_2D;
    static INPUTCORE_API const MInputKey Mouse_ScrollUp;
    static INPUTCORE_API const MInputKey Mouse_ScrollDown;
    static INPUTCORE_API const MInputKey Mouse_WheelAxis;
    static INPUTCORE_API const MInputKey Mouse_LeftButton;
    static INPUTCORE_API const MInputKey Mouse_RightButton;
    static INPUTCORE_API const MInputKey Mouse_MiddleButton;
    static INPUTCORE_API const MInputKey Mouse_XButton;
    static INPUTCORE_API const MInputKey Mouse_XButton2;
  };

} // namespace MEngine::InputCore 

} // namespace MEngine


#endif // _ME_INPUTCORE_GLOBALS_KEYGLOBALS_