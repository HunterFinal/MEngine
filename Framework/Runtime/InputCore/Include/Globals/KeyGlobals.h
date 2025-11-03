#pragma once

#ifndef _ME_INPUTCORE_GLOBALS_KEYGLOBALS_
#define _ME_INPUTCORE_GLOBALS_KEYGLOBALS_

#include "Internal/InputCoreDefines.h"
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
    static INPUTCORE_API const MInputKey Invalid;
    // Mouse input keys

    // Mouse move input
    static INPUTCORE_API const MInputKey Mouse_X;
    static INPUTCORE_API const MInputKey Mouse_Y;
    static INPUTCORE_API const MInputKey Mouse_2D;

    // Mouse wheel input
    static INPUTCORE_API const MInputKey Mouse_ScrollUp;
    static INPUTCORE_API const MInputKey Mouse_ScrollDown;
    static INPUTCORE_API const MInputKey Mouse_WheelAxis;

    // Mouse button input
    static INPUTCORE_API const MInputKey Mouse_LeftButton;
    static INPUTCORE_API const MInputKey Mouse_RightButton;
    static INPUTCORE_API const MInputKey Mouse_MiddleButton;
    static INPUTCORE_API const MInputKey Mouse_XButton;
    static INPUTCORE_API const MInputKey Mouse_XButton2;

    // Keyboard input keys

    // Keyboard alphabets
    static INPUTCORE_API const MInputKey A;
    static INPUTCORE_API const MInputKey B;
    static INPUTCORE_API const MInputKey C;
    static INPUTCORE_API const MInputKey D;
    static INPUTCORE_API const MInputKey E;
    static INPUTCORE_API const MInputKey F;
    static INPUTCORE_API const MInputKey G;
    static INPUTCORE_API const MInputKey H;
    static INPUTCORE_API const MInputKey I;
    static INPUTCORE_API const MInputKey J;
    static INPUTCORE_API const MInputKey K;
    static INPUTCORE_API const MInputKey L;
    static INPUTCORE_API const MInputKey M;
    static INPUTCORE_API const MInputKey N;
    static INPUTCORE_API const MInputKey O;
    static INPUTCORE_API const MInputKey P;
    static INPUTCORE_API const MInputKey Q;
    static INPUTCORE_API const MInputKey R;
    static INPUTCORE_API const MInputKey S;
    static INPUTCORE_API const MInputKey T;
    static INPUTCORE_API const MInputKey U;
    static INPUTCORE_API const MInputKey V;
    static INPUTCORE_API const MInputKey W;
    static INPUTCORE_API const MInputKey X;
    static INPUTCORE_API const MInputKey Y;
    static INPUTCORE_API const MInputKey Z;

    // Keyboard numbers(not numpad)
    static INPUTCORE_API const MInputKey Zero;
    static INPUTCORE_API const MInputKey One;
    static INPUTCORE_API const MInputKey Two;
    static INPUTCORE_API const MInputKey Three;
    static INPUTCORE_API const MInputKey Four;
    static INPUTCORE_API const MInputKey Five;
    static INPUTCORE_API const MInputKey Six;
    static INPUTCORE_API const MInputKey Seven;
    static INPUTCORE_API const MInputKey Eight;
    static INPUTCORE_API const MInputKey Nine;

    // Keyboard numbers(numpad)
    static INPUTCORE_API const MInputKey NumpadZero;
    static INPUTCORE_API const MInputKey NumpadOne;
    static INPUTCORE_API const MInputKey NumpadTwo;
    static INPUTCORE_API const MInputKey NumpadThree;
    static INPUTCORE_API const MInputKey NumpadFour;
    static INPUTCORE_API const MInputKey NumpadFive;
    static INPUTCORE_API const MInputKey NumpadSix;
    static INPUTCORE_API const MInputKey NumpadSeven;
    static INPUTCORE_API const MInputKey NumpadEight;
    static INPUTCORE_API const MInputKey NumpadNine;

    // Keyboard operator keys
    static INPUTCORE_API const MInputKey Add;
    static INPUTCORE_API const MInputKey Subtract;
    static INPUTCORE_API const MInputKey Multiply;
    static INPUTCORE_API const MInputKey Divide;

    // Keyboard printable keys
    static INPUTCORE_API const MInputKey SpaceBar;

    // Keyboard function keys
    static INPUTCORE_API const MInputKey F1;
    static INPUTCORE_API const MInputKey F2;
    static INPUTCORE_API const MInputKey F3;
    static INPUTCORE_API const MInputKey F4;
    static INPUTCORE_API const MInputKey F5;
    static INPUTCORE_API const MInputKey F6;
    static INPUTCORE_API const MInputKey F7;
    static INPUTCORE_API const MInputKey F8;
    static INPUTCORE_API const MInputKey F9;
    static INPUTCORE_API const MInputKey F10;
    static INPUTCORE_API const MInputKey F11;
    static INPUTCORE_API const MInputKey F12;
    static INPUTCORE_API const MInputKey Escape;
    static INPUTCORE_API const MInputKey Pause;

    // Keyboard modifier keys
    static INPUTCORE_API const MInputKey LeftShift;
    static INPUTCORE_API const MInputKey RightShift;
    static INPUTCORE_API const MInputKey LeftControl;
    static INPUTCORE_API const MInputKey RightControl;
    static INPUTCORE_API const MInputKey LeftAlt;
    static INPUTCORE_API const MInputKey RightAlt;
    static INPUTCORE_API const MInputKey LeftCommand;
    static INPUTCORE_API const MInputKey RightCommand;

    // Keyboard toggle keys
    static INPUTCORE_API const MInputKey CapsLock;
    static INPUTCORE_API const MInputKey NumLock;
    static INPUTCORE_API const MInputKey ScrollLock;

    // Keyboard navigation keys
    static INPUTCORE_API const MInputKey ArrowLeft;
    static INPUTCORE_API const MInputKey ArrowUp;
    static INPUTCORE_API const MInputKey ArrowRight;
    static INPUTCORE_API const MInputKey ArrowDown;
    static INPUTCORE_API const MInputKey PageUp;
    static INPUTCORE_API const MInputKey PageDown;
    static INPUTCORE_API const MInputKey Home;
    static INPUTCORE_API const MInputKey End;
    static INPUTCORE_API const MInputKey Insert;
    static INPUTCORE_API const MInputKey Delete;

    // Keyboard editing keys
    static INPUTCORE_API const MInputKey Backspace;
    static INPUTCORE_API const MInputKey Tab;
    static INPUTCORE_API const MInputKey Enter;
    static INPUTCORE_API const MInputKey Decimal;

    // Keyboard symbol keys
    static INPUTCORE_API const MInputKey Semicolon;
    static INPUTCORE_API const MInputKey Equals;
    static INPUTCORE_API const MInputKey Comma;
    static INPUTCORE_API const MInputKey Underscore;
    static INPUTCORE_API const MInputKey Hyphen;
    static INPUTCORE_API const MInputKey Period;
    static INPUTCORE_API const MInputKey Slash;
    static INPUTCORE_API const MInputKey BackSlash;
    static INPUTCORE_API const MInputKey Tilde;
    static INPUTCORE_API const MInputKey LeftBracket;
    static INPUTCORE_API const MInputKey RightBracket;
    static INPUTCORE_API const MInputKey Apostrophe;
    static INPUTCORE_API const MInputKey Quote;

    static INPUTCORE_API const MInputKey Ampersand;
    static INPUTCORE_API const MInputKey Asterix;
    static INPUTCORE_API const MInputKey Caret;
    static INPUTCORE_API const MInputKey Colon;
    static INPUTCORE_API const MInputKey Dollar;
    static INPUTCORE_API const MInputKey Exclamation;
    static INPUTCORE_API const MInputKey LeftParantheses;
    static INPUTCORE_API const MInputKey RightParantheses;

    static INPUTCORE_API const MInputKey A_AccentGrave;
    static INPUTCORE_API const MInputKey E_AccentGrave;
    static INPUTCORE_API const MInputKey E_AccentAigu;
    static INPUTCORE_API const MInputKey C_Cedille;
    static INPUTCORE_API const MInputKey Section;

    // NOTE Copied from unreal engine
    // Platform Keys
    // These keys platform specific versions of keys that go by different names.
    // The delete key is a good example, on Windows Delete is the virtual key for Delete.
    // On Macs, the Delete key is the virtual key for BackSpace.
    static INPUTCORE_API const MInputKey Platform_Delete;

    // Gamepad Keys

    // Gamepad stick input keys
    static INPUTCORE_API const MInputKey Gamepad_LeftX;
    static INPUTCORE_API const MInputKey Gamepad_LeftY;
    static INPUTCORE_API const MInputKey Gamepad_Left2D;
    static INPUTCORE_API const MInputKey Gamepad_LeftThumbstick;
    static INPUTCORE_API const MInputKey Gamepad_RightX;
    static INPUTCORE_API const MInputKey Gamepad_RightY;
    static INPUTCORE_API const MInputKey Gamepad_Right2D;
    static INPUTCORE_API const MInputKey Gamepad_RightThumbstick;

    // Gamepad button input keys
    static INPUTCORE_API const MInputKey Gamepad_LeftTriggerAxis;
    static INPUTCORE_API const MInputKey Gamepad_RightTriggerAxis;
    static INPUTCORE_API const MInputKey Gamepad_FaceButton_East;
    static INPUTCORE_API const MInputKey Gamepad_FaceButton_South;
    static INPUTCORE_API const MInputKey Gamepad_FaceButton_West;
    static INPUTCORE_API const MInputKey Gamepad_FaceButton_North;
    static INPUTCORE_API const MInputKey Gamepad_LeftShoulder;
    static INPUTCORE_API const MInputKey Gamepad_RightShoulder;
    static INPUTCORE_API const MInputKey Gamepad_LeftTrigger;
    static INPUTCORE_API const MInputKey Gamepad_RightTrigger;

    // Gamepad DPad input keys
    static INPUTCORE_API const MInputKey Gamepad_DPad_Up;
    static INPUTCORE_API const MInputKey Gamepad_DPad_Right;
    static INPUTCORE_API const MInputKey Gamepad_DPad_Down;
    static INPUTCORE_API const MInputKey Gamepad_DPad_Left;

    // Gamepad stick virtual keys for press/release emulation
    static INPUTCORE_API const MInputKey Gamepad_Vir_LeftStick_Up;
    static INPUTCORE_API const MInputKey Gamepad_Vir_LeftStick_Right;
    static INPUTCORE_API const MInputKey Gamepad_Vir_LeftStick_Down;
    static INPUTCORE_API const MInputKey Gamepad_Vir_LeftStick_Left;
    static INPUTCORE_API const MInputKey Gamepad_Vir_RightStick_Up;
    static INPUTCORE_API const MInputKey Gamepad_Vir_RightStick_Right;
    static INPUTCORE_API const MInputKey Gamepad_Vir_RightStick_Down;
    static INPUTCORE_API const MInputKey Gamepad_Vir_RightStick_Left;

  };

} // namespace MEngine::InputCore 

} // namespace MEngine


#endif // _ME_INPUTCORE_GLOBALS_KEYGLOBALS_