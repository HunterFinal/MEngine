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
const MInputKey GStaticKeys::Invalid{INVALID_KEY_NAME};

// Mouse input keys

// Mouse move input
const MInputKey GStaticKeys::Mouse_X{MTEXT("Mouse_X")};
const MInputKey GStaticKeys::Mouse_Y{MTEXT("Mouse_Y")};
const MInputKey GStaticKeys::Mouse_2D{MTEXT("Mouse_2D")};

// Mouse wheel input
const MInputKey GStaticKeys::Mouse_ScrollUp{MTEXT("Mouse_ScrollUp")};
const MInputKey GStaticKeys::Mouse_ScrollDown{MTEXT("Mouse_ScrollDown")};
const MInputKey GStaticKeys::Mouse_WheelAxis{MTEXT("Mouse_WheelAxis")};

// Mouse button input
const MInputKey GStaticKeys::Mouse_LeftButton{MTEXT("Mouse_LeftButton")};
const MInputKey GStaticKeys::Mouse_RightButton{MTEXT("Mouse_RightButton")};
const MInputKey GStaticKeys::Mouse_MiddleButton{MTEXT("Mouse_MiddleButton")};
const MInputKey GStaticKeys::Mouse_XButton{MTEXT("Mouse_XButton")};
const MInputKey GStaticKeys::Mouse_XButton2{MTEXT("Mouse_XButton2")};

// Keyboard input keys

// Keyboard Alphabet
const MInputKey GStaticKeys::A{MTEXT("A")};
const MInputKey GStaticKeys::B{MTEXT("B")};
const MInputKey GStaticKeys::C{MTEXT("C")};
const MInputKey GStaticKeys::D{MTEXT("D")};
const MInputKey GStaticKeys::E{MTEXT("E")};
const MInputKey GStaticKeys::F{MTEXT("F")};
const MInputKey GStaticKeys::G{MTEXT("G")};
const MInputKey GStaticKeys::H{MTEXT("H")};
const MInputKey GStaticKeys::I{MTEXT("I")};
const MInputKey GStaticKeys::J{MTEXT("J")};
const MInputKey GStaticKeys::K{MTEXT("K")};
const MInputKey GStaticKeys::L{MTEXT("L")};
const MInputKey GStaticKeys::M{MTEXT("M")};
const MInputKey GStaticKeys::N{MTEXT("N")};
const MInputKey GStaticKeys::O{MTEXT("O")};
const MInputKey GStaticKeys::P{MTEXT("P")};
const MInputKey GStaticKeys::Q{MTEXT("Q")};
const MInputKey GStaticKeys::R{MTEXT("R")};
const MInputKey GStaticKeys::S{MTEXT("S")};
const MInputKey GStaticKeys::T{MTEXT("T")};
const MInputKey GStaticKeys::U{MTEXT("U")};
const MInputKey GStaticKeys::V{MTEXT("V")};
const MInputKey GStaticKeys::W{MTEXT("W")};
const MInputKey GStaticKeys::X{MTEXT("X")};
const MInputKey GStaticKeys::Y{MTEXT("Y")};
const MInputKey GStaticKeys::Z{MTEXT("Z")};

// Keyboard numbers(not numpad)
const MInputKey GStaticKeys::Zero{MTEXT("Zero")};
const MInputKey GStaticKeys::One{MTEXT("One")};
const MInputKey GStaticKeys::Two{MTEXT("Two")};
const MInputKey GStaticKeys::Three{MTEXT("Three")};
const MInputKey GStaticKeys::Four{MTEXT("Four")};
const MInputKey GStaticKeys::Five{MTEXT("Five")};
const MInputKey GStaticKeys::Six{MTEXT("Six")};
const MInputKey GStaticKeys::Seven{MTEXT("Seven")};
const MInputKey GStaticKeys::Eight{MTEXT("Eight")};
const MInputKey GStaticKeys::Nine{MTEXT("Nine")};

// Keyboard numbers(numpad)
const MInputKey GStaticKeys::NumpadZero{MTEXT("NumpadZero")};
const MInputKey GStaticKeys::NumpadOne{MTEXT("NumpadOne")};
const MInputKey GStaticKeys::NumpadTwo{MTEXT("NumpadTwo")};
const MInputKey GStaticKeys::NumpadThree{MTEXT("NumpadThree")};
const MInputKey GStaticKeys::NumpadFour{MTEXT("NumpadFour")};
const MInputKey GStaticKeys::NumpadFive{MTEXT("NumpadFive")};
const MInputKey GStaticKeys::NumpadSix{MTEXT("NumpadSix")};
const MInputKey GStaticKeys::NumpadSeven{MTEXT("NumpadSeven")};
const MInputKey GStaticKeys::NumpadEight{MTEXT("NumpadEight")};
const MInputKey GStaticKeys::NumpadNine{MTEXT("NumpadNine")};

// Keyboard operator keys
const MInputKey GStaticKeys::Add{MTEXT("Add")};
const MInputKey GStaticKeys::Subtract{MTEXT("Subtract")};
const MInputKey GStaticKeys::Multiply{MTEXT("Multiply")};
const MInputKey GStaticKeys::Divide{MTEXT("Divide")};

// Keyboard printable keys
const MInputKey GStaticKeys::SpaceBar{MTEXT("SpaceBar")};

// Keyboard function keys
const MInputKey GStaticKeys::F1{MTEXT("F1")};
const MInputKey GStaticKeys::F2{MTEXT("F2")};
const MInputKey GStaticKeys::F3{MTEXT("F3")};
const MInputKey GStaticKeys::F4{MTEXT("F4")};
const MInputKey GStaticKeys::F5{MTEXT("F5")};
const MInputKey GStaticKeys::F6{MTEXT("F6")};
const MInputKey GStaticKeys::F7{MTEXT("F7")};
const MInputKey GStaticKeys::F8{MTEXT("F8")};
const MInputKey GStaticKeys::F9{MTEXT("F9")};
const MInputKey GStaticKeys::F10{MTEXT("F10")};
const MInputKey GStaticKeys::F11{MTEXT("F11")};
const MInputKey GStaticKeys::F12{MTEXT("F12")};
const MInputKey GStaticKeys::Escape{MTEXT("Escape")};
const MInputKey GStaticKeys::Pause{MTEXT("Pause")};

// Keyboard modifier keys
const MInputKey GStaticKeys::LeftShift{MTEXT("LeftShift")};
const MInputKey GStaticKeys::RightShift{MTEXT("RightShift")};
const MInputKey GStaticKeys::LeftControl{MTEXT("LeftControl")};
const MInputKey GStaticKeys::RightControl{MTEXT("RightControl")};
const MInputKey GStaticKeys::LeftAlt{MTEXT("LeftAlt")};
const MInputKey GStaticKeys::RightAlt{MTEXT("RightAlt")};
const MInputKey GStaticKeys::LeftCommand{MTEXT("LeftCommand")};
const MInputKey GStaticKeys::RightCommand{MTEXT("RightCommand")};

// Keyboard toggle keys
const MInputKey GStaticKeys::CapsLock{MTEXT("CapsLock")};
const MInputKey GStaticKeys::NumLock{MTEXT("NumLock")};
const MInputKey GStaticKeys::ScrollLock{MTEXT("ScrollLock")};

// Keyboard navigation keys
const MInputKey GStaticKeys::ArrowLeft{MTEXT("ArrowLeft")};
const MInputKey GStaticKeys::ArrowUp{MTEXT("ArrowUp")};
const MInputKey GStaticKeys::ArrowRight{MTEXT("ArrowRight")};
const MInputKey GStaticKeys::ArrowDown{MTEXT("ArrowDown")};
const MInputKey GStaticKeys::PageUp{MTEXT("PageUp")};
const MInputKey GStaticKeys::PageDown{MTEXT("PageDown")};
const MInputKey GStaticKeys::Home{MTEXT("Home")};
const MInputKey GStaticKeys::End{MTEXT("End")};
const MInputKey GStaticKeys::Insert{MTEXT("Insert")};
const MInputKey GStaticKeys::Delete{MTEXT("Delete")};

// Keyboard editing keys
const MInputKey GStaticKeys::Backspace{MTEXT("Backspace")};
const MInputKey GStaticKeys::Tab{MTEXT("Tab")};
const MInputKey GStaticKeys::Enter{MTEXT("Enter")};
const MInputKey GStaticKeys::Decimal{MTEXT("Decimal")};

// Keyboard symbol keys
const MInputKey GStaticKeys::Semicolon{MTEXT("Semicolon")};
const MInputKey GStaticKeys::Equals{MTEXT("Equals")};
const MInputKey GStaticKeys::Comma{MTEXT("Comma")};
const MInputKey GStaticKeys::Underscore{MTEXT("Underscore")};
const MInputKey GStaticKeys::Hyphen{MTEXT("Hyphen")};
const MInputKey GStaticKeys::Period{MTEXT("Period")};
const MInputKey GStaticKeys::Slash{MTEXT("Slash")};
const MInputKey GStaticKeys::BackSlash{MTEXT("BackSlash")};
const MInputKey GStaticKeys::Tilde{MTEXT("Tilde")};
const MInputKey GStaticKeys::LeftBracket{MTEXT("LeftBracket")};
const MInputKey GStaticKeys::RightBracket{MTEXT("RightBracket")};
const MInputKey GStaticKeys::Apostrophe{MTEXT("Apostrophe")};
const MInputKey GStaticKeys::Quote{MTEXT("Quote")};

const MInputKey GStaticKeys::Ampersand{MTEXT("Ampersand")};
const MInputKey GStaticKeys::Asterix{MTEXT("Asterix")};
const MInputKey GStaticKeys::Caret{MTEXT("Caret")};
const MInputKey GStaticKeys::Colon{MTEXT("Colon")};
const MInputKey GStaticKeys::Dollar{MTEXT("Dollar")};
const MInputKey GStaticKeys::Exclamation{MTEXT("Exclamation")};
const MInputKey GStaticKeys::LeftParantheses{MTEXT("LeftParantheses")};
const MInputKey GStaticKeys::RightParantheses{MTEXT("RightParantheses")};

const MInputKey GStaticKeys::A_AccentGrave{MTEXT("A_AccentGrave")};
const MInputKey GStaticKeys::E_AccentGrave{MTEXT("E_AccentGrave")};
const MInputKey GStaticKeys::E_AccentAigu{MTEXT("E_AccentAigu")};
const MInputKey GStaticKeys::C_Cedille{MTEXT("C_Cedille")};
const MInputKey GStaticKeys::Section{MTEXT("Section")};

// Platform Keys
// TODO
const MInputKey GStaticKeys::Platform_Delete = GStaticKeys::Delete;

// Gamepad Keys

// Gamepad stick input keys
const MInputKey GStaticKeys::Gamepad_LeftX{MTEXT("Gamepad_LeftX")};
const MInputKey GStaticKeys::Gamepad_LeftY{MTEXT("Gamepad_LeftY")};
const MInputKey GStaticKeys::Gamepad_Left2D{MTEXT("Gamepad_Left2D")};
const MInputKey GStaticKeys::Gamepad_LeftThumbstick{MTEXT("Gamepad_LeftThumbstick")};
const MInputKey GStaticKeys::Gamepad_RightX{MTEXT("Gamepad_RightX")};
const MInputKey GStaticKeys::Gamepad_RightY{MTEXT("Gamepad_RightY")};
const MInputKey GStaticKeys::Gamepad_Right2D{MTEXT("Gamepad_Right2D")};
const MInputKey GStaticKeys::Gamepad_RightThumbstick{MTEXT("Gamepad_RightThumbstick")};

// Gamepad button input keys
const MInputKey GStaticKeys::Gamepad_LeftTriggerAxis{MTEXT("Gamepad_LeftTriggerAxis")};
const MInputKey GStaticKeys::Gamepad_RightTriggerAxis{MTEXT("Gamepad_RightTriggerAxis")};
const MInputKey GStaticKeys::Gamepad_FaceButton_East{MTEXT("Gamepad_FaceButton_East")};
const MInputKey GStaticKeys::Gamepad_FaceButton_South{MTEXT("Gamepad_FaceButton_South")};
const MInputKey GStaticKeys::Gamepad_FaceButton_West{MTEXT("Gamepad_FaceButton_West")};
const MInputKey GStaticKeys::Gamepad_FaceButton_North{MTEXT("Gamepad_FaceButton_North")};
const MInputKey GStaticKeys::Gamepad_LeftShoulder{MTEXT("Gamepad_LeftShoulder")};
const MInputKey GStaticKeys::Gamepad_RightShoulder{MTEXT("Gamepad_RightShoulder")};
const MInputKey GStaticKeys::Gamepad_LeftTrigger{MTEXT("Gamepad_LeftTrigger")};
const MInputKey GStaticKeys::Gamepad_RightTrigger{MTEXT("Gamepad_RightTrigger")};

// Gamepad DPad input keys
const MInputKey GStaticKeys::Gamepad_DPad_Up{MTEXT("Gamepad_DPad_Up")};
const MInputKey GStaticKeys::Gamepad_DPad_Right{MTEXT("Gamepad_DPad_Right")};
const MInputKey GStaticKeys::Gamepad_DPad_Down{MTEXT("Gamepad_DPad_Down")};
const MInputKey GStaticKeys::Gamepad_DPad_Left{MTEXT("Gamepad_DPad_Left")};

// Gamepad stick virtual keys for press/release emulation
const MInputKey GStaticKeys::Gamepad_Vir_LeftStick_Up{MTEXT("Gamepad_Vir_LeftStick_Up")};
const MInputKey GStaticKeys::Gamepad_Vir_LeftStick_Right{MTEXT("Gamepad_Vir_LeftStick_Right")};
const MInputKey GStaticKeys::Gamepad_Vir_LeftStick_Down{MTEXT("Gamepad_Vir_LeftStick_Down")};
const MInputKey GStaticKeys::Gamepad_Vir_LeftStick_Left{MTEXT("Gamepad_Vir_LeftStick_Left")};
const MInputKey GStaticKeys::Gamepad_Vir_RightStick_Up{MTEXT("Gamepad_Vir_RightStick_Up")};
const MInputKey GStaticKeys::Gamepad_Vir_RightStick_Right{MTEXT("Gamepad_Vir_RightStick_Right")};
const MInputKey GStaticKeys::Gamepad_Vir_RightStick_Down{MTEXT("Gamepad_Vir_RightStick_Down")};
const MInputKey GStaticKeys::Gamepad_Vir_RightStick_Left{MTEXT("Gamepad_Vir_RightStick_Left")};

} // namespace MEngine::InputCore

} // namespace MEngine