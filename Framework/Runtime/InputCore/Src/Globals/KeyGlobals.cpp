#include "Globals/KeyGlobals.h"
#include "Core/InputKey.h"

#include <string_view>

namespace MEngine
{

namespace InputCore
{

const MInputKey::KeyNameType INVALID_KEY_NAME{MTEXT("Invalid Key Name")};
const MInputKey::KeyNameType INVALID_KEY_DISPLAY_NAME{MTEXT("Invalid Display Name")};
const MInputKey::KeyNameType INVALID_KEY_CATEGORY{MTEXT("Invalid Key Category")};
const MInputKey::KeyNameType NAME_KEYBOARD_CATEGORY{MTEXT("Keyboard")};
const MInputKey::KeyNameType NAME_GAMEPAD_CATEGORY{MTEXT("Gamepad")};
const MInputKey::KeyNameType NAME_MOUSE_CATEGORY{MTEXT("Mouse")};

const MInputKey GStaticKeys::Any{MTEXT("Any")};

// Mouse input keys
const MInputKey GStaticKeys::Mouse_X{MTEXT("Mouse_X")};
const MInputKey GStaticKeys::Mouse_Y{MTEXT("Mouse_Y")};
const MInputKey GStaticKeys::Mouse_2D{MTEXT("Mouse_2D")};
const MInputKey GStaticKeys::Mouse_ScrollUp{MTEXT("Mouse_ScrollUp")};
const MInputKey GStaticKeys::Mouse_ScrollDown{MTEXT("Mouse_ScrollDown")};
const MInputKey GStaticKeys::Mouse_WheelAxis{MTEXT("Mouse_WheelAxis")};
const MInputKey GStaticKeys::Mouse_LeftButton{MTEXT("Mouse_LeftButton")};
const MInputKey GStaticKeys::Mouse_RightButton{MTEXT("Mouse_RightButton")};
const MInputKey GStaticKeys::Mouse_MiddleButton{MTEXT("Mouse_MiddleButton")};
const MInputKey GStaticKeys::Mouse_XButton{MTEXT("Mouse_XButton")};
const MInputKey GStaticKeys::Mouse_XButton2{MTEXT("Mouse_XButton2")};
  
}

}