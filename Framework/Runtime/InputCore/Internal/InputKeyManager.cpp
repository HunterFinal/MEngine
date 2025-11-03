#include "IInputKeyManager.h"

#include "Core/InputKey.h"
#include "Core/InputKeyProxy.h"
#include "Core/InputKeyTypes.h"
#include "Globals/KeyGlobals.h"
#include "Internal/IInputProxyFactory.h"
#include "Macro/AssertionMacros.h"

#include <unordered_map>
#include <memory>
#include <string_view>

namespace MEngine
{

namespace InputCore
{

class MInputKeyProxyFactory final : public MEngine::InputCore::IInputProxyFactory
{
  ~MInputKeyProxyFactory() = default;

  std::shared_ptr<IInputKeyProxy> MakeInputKeyProxy(IN const MInputKey InInputKey, IN StringView InLongDisplayName, IN const uint32 InKeyFlags, IN StringView InShortDisplayName, IN StringView InKeyCategory) const override final
  {
    return std::make_shared<MInputKeyProxy>(InInputKey, InLongDisplayName, InShortDisplayName, InKeyCategory, InKeyFlags);
  }
};


class MInputKeyManager : public MEngine::InputCore::IInputKeyManager
{
public:
  static MInputKeyManager& GetInstance()
  {
    static MInputKeyManager sInstance;
    return sInstance;
  }

  virtual void Initialize() override
  {
    if (bIsInitialized)
    {
      // TODO Add debug message
      return;
    }

    bIsInitialized = true;

    std::unique_ptr<IInputProxyFactory> proxyFactory = std::make_unique<MInputKeyProxyFactory>();

    #define PROXY(...) proxyFactory->MakeInputKeyProxy(__VA_ARGS__)

    auto formatNameFunc = [](IN const TCHAR* InName)
    {
      return StringView{InName};
    };

    AddKey(PROXY(GStaticKeys::Any, formatNameFunc(MTEXT("Any Key"))));

    // Mouse input keys

    // Mouse move input
    AddKey(PROXY(GStaticKeys::Mouse_X, formatNameFunc(MTEXT("Mouse X")), MInputKeyProxy::Axis1D | MInputKeyProxy::MouseButtonKey | MInputKeyProxy::UpdateAxisWithoutSamples));
    AddKey(PROXY(GStaticKeys::Mouse_Y, formatNameFunc(MTEXT("Mouse Y")), MInputKeyProxy::Axis1D | MInputKeyProxy::MouseButtonKey | MInputKeyProxy::UpdateAxisWithoutSamples));
    AddPairedKey(PROXY(GStaticKeys::Mouse_2D, formatNameFunc(MTEXT("Mouse XY 2D-Axis")), MInputKeyProxy::Axis2D | MInputKeyProxy::MouseButtonKey | MInputKeyProxy::UpdateAxisWithoutSamples), GStaticKeys::Mouse_X, GStaticKeys::Mouse_Y);
    // Mouse wheel input
    AddKey(PROXY(GStaticKeys::Mouse_ScrollUp, formatNameFunc(MTEXT("Mouse Wheel Scroll Up")), MInputKeyProxy::MouseButtonKey | MInputKeyProxy::ButtonAxis));
    AddKey(PROXY(GStaticKeys::Mouse_ScrollUp, formatNameFunc(MTEXT("Mouse Wheel Scroll Up")), MInputKeyProxy::MouseButtonKey | MInputKeyProxy::ButtonAxis));
    AddKey(PROXY(GStaticKeys::Mouse_WheelAxis, formatNameFunc(MTEXT("Mouse Wheel Axis")), MInputKeyProxy::Axis1D | MInputKeyProxy::MouseButtonKey | MInputKeyProxy::UpdateAxisWithoutSamples));
    // Mouse button input
    AddKey(PROXY(GStaticKeys::Mouse_LeftButton, formatNameFunc(MTEXT("Mouse Left Button")), MInputKeyProxy::MouseButtonKey, formatNameFunc(MTEXT("MLB"))));
    AddKey(PROXY(GStaticKeys::Mouse_RightButton, formatNameFunc(MTEXT("Mouse Right Button")), MInputKeyProxy::MouseButtonKey, formatNameFunc(MTEXT("MRB"))));
    AddKey(PROXY(GStaticKeys::Mouse_MiddleButton, formatNameFunc(MTEXT("Mouse Middle Button")), MInputKeyProxy::MouseButtonKey, formatNameFunc(MTEXT("MMB"))));
    AddKey(PROXY(GStaticKeys::Mouse_XButton, formatNameFunc(MTEXT("Mouse X Button")), MInputKeyProxy::MouseButtonKey, formatNameFunc(MTEXT("MXB"))));
    AddKey(PROXY(GStaticKeys::Mouse_XButton2, formatNameFunc(MTEXT("Mouse X Button2")), MInputKeyProxy::MouseButtonKey, formatNameFunc(MTEXT("MXB2"))));

    // Keyboard input keys

    // Keyboard alphabets
    AddKey(PROXY(GStaticKeys::A, formatNameFunc(MTEXT("A"))));
    AddKey(PROXY(GStaticKeys::B, formatNameFunc(MTEXT("B"))));
    AddKey(PROXY(GStaticKeys::C, formatNameFunc(MTEXT("C"))));
    AddKey(PROXY(GStaticKeys::D, formatNameFunc(MTEXT("D"))));
    AddKey(PROXY(GStaticKeys::E, formatNameFunc(MTEXT("E"))));
    AddKey(PROXY(GStaticKeys::F, formatNameFunc(MTEXT("F"))));
    AddKey(PROXY(GStaticKeys::G, formatNameFunc(MTEXT("G"))));
    AddKey(PROXY(GStaticKeys::H, formatNameFunc(MTEXT("H"))));
    AddKey(PROXY(GStaticKeys::I, formatNameFunc(MTEXT("I"))));
    AddKey(PROXY(GStaticKeys::J, formatNameFunc(MTEXT("J"))));
    AddKey(PROXY(GStaticKeys::K, formatNameFunc(MTEXT("K"))));
    AddKey(PROXY(GStaticKeys::L, formatNameFunc(MTEXT("L"))));
    AddKey(PROXY(GStaticKeys::M, formatNameFunc(MTEXT("M"))));
    AddKey(PROXY(GStaticKeys::N, formatNameFunc(MTEXT("N"))));
    AddKey(PROXY(GStaticKeys::O, formatNameFunc(MTEXT("O"))));
    AddKey(PROXY(GStaticKeys::P, formatNameFunc(MTEXT("P"))));
    AddKey(PROXY(GStaticKeys::Q, formatNameFunc(MTEXT("Q"))));
    AddKey(PROXY(GStaticKeys::R, formatNameFunc(MTEXT("R"))));
    AddKey(PROXY(GStaticKeys::S, formatNameFunc(MTEXT("S"))));
    AddKey(PROXY(GStaticKeys::T, formatNameFunc(MTEXT("T"))));
    AddKey(PROXY(GStaticKeys::U, formatNameFunc(MTEXT("U"))));
    AddKey(PROXY(GStaticKeys::V, formatNameFunc(MTEXT("V"))));
    AddKey(PROXY(GStaticKeys::W, formatNameFunc(MTEXT("W"))));
    AddKey(PROXY(GStaticKeys::X, formatNameFunc(MTEXT("X"))));
    AddKey(PROXY(GStaticKeys::Y, formatNameFunc(MTEXT("Y"))));
    AddKey(PROXY(GStaticKeys::Z, formatNameFunc(MTEXT("Z"))));

    // Keyboard numbers(not numpad)
    AddKey(PROXY(GStaticKeys::Zero, formatNameFunc(MTEXT("Zero"))));
    AddKey(PROXY(GStaticKeys::One, formatNameFunc(MTEXT("One"))));
    AddKey(PROXY(GStaticKeys::Two, formatNameFunc(MTEXT("Two"))));
    AddKey(PROXY(GStaticKeys::Three, formatNameFunc(MTEXT("Three"))));
    AddKey(PROXY(GStaticKeys::Four, formatNameFunc(MTEXT("Four"))));
    AddKey(PROXY(GStaticKeys::Five, formatNameFunc(MTEXT("Five"))));
    AddKey(PROXY(GStaticKeys::Six, formatNameFunc(MTEXT("Six"))));
    AddKey(PROXY(GStaticKeys::Seven, formatNameFunc(MTEXT("Seven"))));
    AddKey(PROXY(GStaticKeys::Eight, formatNameFunc(MTEXT("Eight"))));
    AddKey(PROXY(GStaticKeys::Nine, formatNameFunc(MTEXT("Nine"))));

    // Keyboard numbers(numpad)
    AddKey(PROXY(GStaticKeys::NumpadZero, formatNameFunc(MTEXT("Numpad Zero")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 0"))));
    AddKey(PROXY(GStaticKeys::NumpadOne, formatNameFunc(MTEXT("Numpad One")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 1"))));
    AddKey(PROXY(GStaticKeys::NumpadTwo, formatNameFunc(MTEXT("Numpad Two")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 2"))));
    AddKey(PROXY(GStaticKeys::NumpadThree, formatNameFunc(MTEXT("Numpad Three")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 3"))));
    AddKey(PROXY(GStaticKeys::NumpadFour, formatNameFunc(MTEXT("Numpad Four")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 4"))));
    AddKey(PROXY(GStaticKeys::NumpadFive, formatNameFunc(MTEXT("Numpad Five")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 5"))));
    AddKey(PROXY(GStaticKeys::NumpadSix, formatNameFunc(MTEXT("Numpad Six")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 6"))));
    AddKey(PROXY(GStaticKeys::NumpadSeven, formatNameFunc(MTEXT("Numpad Seven")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 7"))));
    AddKey(PROXY(GStaticKeys::NumpadEight, formatNameFunc(MTEXT("Numpad Eight")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 8"))));
    AddKey(PROXY(GStaticKeys::NumpadNine, formatNameFunc(MTEXT("Numpad Nine")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num 9"))));

    // Keyboard operator keys
    AddKey(PROXY(GStaticKeys::Add, formatNameFunc(MTEXT("Add")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num +"))));
    AddKey(PROXY(GStaticKeys::Subtract, formatNameFunc(MTEXT("Subtract")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num -"))));
    AddKey(PROXY(GStaticKeys::Multiply, formatNameFunc(MTEXT("Multiply")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num *"))));
    AddKey(PROXY(GStaticKeys::Divide, formatNameFunc(MTEXT("Divide")), MInputKeyProxy::None, formatNameFunc(MTEXT("Num /"))));
    
    // Keyboard printable keys
    AddKey(PROXY(GStaticKeys::SpaceBar, formatNameFunc(MTEXT("Space Bar")), MInputKeyProxy::None, formatNameFunc(MTEXT("Space"))));

    // Keyboard function keys
    AddKey(PROXY(GStaticKeys::F1, formatNameFunc(MTEXT("F1"))));
    AddKey(PROXY(GStaticKeys::F2, formatNameFunc(MTEXT("F2"))));
    AddKey(PROXY(GStaticKeys::F3, formatNameFunc(MTEXT("F3"))));
    AddKey(PROXY(GStaticKeys::F4, formatNameFunc(MTEXT("F4"))));
    AddKey(PROXY(GStaticKeys::F5, formatNameFunc(MTEXT("F5"))));
    AddKey(PROXY(GStaticKeys::F6, formatNameFunc(MTEXT("F6"))));
    AddKey(PROXY(GStaticKeys::F7, formatNameFunc(MTEXT("F7"))));
    AddKey(PROXY(GStaticKeys::F8, formatNameFunc(MTEXT("F8"))));
    AddKey(PROXY(GStaticKeys::F9, formatNameFunc(MTEXT("F9"))));
    AddKey(PROXY(GStaticKeys::F10, formatNameFunc(MTEXT("F10"))));
    AddKey(PROXY(GStaticKeys::F11, formatNameFunc(MTEXT("F11"))));
    AddKey(PROXY(GStaticKeys::F12, formatNameFunc(MTEXT("F12"))));
    AddKey(PROXY(GStaticKeys::Escape, formatNameFunc(MTEXT("Escape")), MInputKeyProxy::None, formatNameFunc(MTEXT("Esc"))));
    AddKey(PROXY(GStaticKeys::Pause, formatNameFunc(MTEXT("Pause"))));

    // Keyboard modifier keys
    AddKey(PROXY(GStaticKeys::LeftShift, formatNameFunc(MTEXT("Left Shift")), MInputKeyProxy::ModifierKey));
    AddKey(PROXY(GStaticKeys::RightShift, formatNameFunc(MTEXT("Right Shift")), MInputKeyProxy::ModifierKey));
    AddKey(PROXY(GStaticKeys::LeftControl, formatNameFunc(MTEXT("Left Control")), MInputKeyProxy::ModifierKey, formatNameFunc(MTEXT("Left Ctrl"))));
    AddKey(PROXY(GStaticKeys::RightControl, formatNameFunc(MTEXT("Right Control")), MInputKeyProxy::ModifierKey, formatNameFunc(MTEXT("Right Ctrl"))));
    AddKey(PROXY(GStaticKeys::LeftAlt, formatNameFunc(MTEXT("Left Alt")), MInputKeyProxy::ModifierKey));
    AddKey(PROXY(GStaticKeys::RightAlt, formatNameFunc(MTEXT("Right Alt")), MInputKeyProxy::ModifierKey));
    AddKey(PROXY(GStaticKeys::LeftCommand, formatNameFunc(MTEXT("Left Command")), MInputKeyProxy::ModifierKey, formatNameFunc(MTEXT("Left CMD"))));
    AddKey(PROXY(GStaticKeys::RightCommand, formatNameFunc(MTEXT("Right Command")), MInputKeyProxy::ModifierKey, formatNameFunc(MTEXT("Right CMD"))));

    // Keyboard toggle keys
    AddKey(PROXY(GStaticKeys::CapsLock, formatNameFunc(MTEXT("Caps Lock")), MInputKeyProxy::None, formatNameFunc(MTEXT("Caps"))));
    AddKey(PROXY(GStaticKeys::NumLock, formatNameFunc(MTEXT("Num Lock"))));
    AddKey(PROXY(GStaticKeys::ScrollLock, formatNameFunc(MTEXT("Scroll Lock"))));

    #undef PROXY
  }

  virtual void AddKey(IN std::shared_ptr<IInputKeyProxy> InKeyProxy) override
  {
    me_assert(InKeyProxy != nullptr);
    MInputKey inputKey = InKeyProxy->GetKey();
    me_assert(!m_inputKeys.contains(inputKey));
    m_inputKeys.emplace(inputKey, InKeyProxy);
  }

  virtual void AddPairedKey(IN std::shared_ptr<IInputKeyProxy> InPairedKeyProxy, IN const IInputKeyProxy& KeyX, IN const IInputKeyProxy& KeyY) override
  {
    me_assert((InPairedKeyProxy != nullptr) && (InPairedKeyProxy->IsAxis2D()));
    me_assert(m_inputKeys.contains(KeyX.GetKey()) && m_inputKeys.contains(KeyY.GetKey()));
    me_assert(KeyX.IsAxis1D() && KeyY.IsAxis1D());
    me_assert((KeyX.GetPairedAxisType() == EPairedAxisType::Unpaired) && KeyY.GetPairedAxisType() == EPairedAxisType::Unpaired);
    
    const bool bCanAddPairedKey =  (InPairedKeyProxy != nullptr) && (InPairedKeyProxy->IsAxis2D())
                                && m_inputKeys.contains(KeyX.GetKey()) && m_inputKeys.contains(KeyY.GetKey())
                                && KeyX.IsAxis1D() && KeyY.IsAxis1D()
                                && (KeyX.GetPairedAxisType() == EPairedAxisType::Unpaired) && (KeyY.GetPairedAxisType() == EPairedAxisType::Unpaired);
    if (!bCanAddPairedKey)
    {
      return;
    }

    AddKey(InPairedKeyProxy);

    m_inputKeys[KeyX.GetKey()]->SetPairedAxisType(EPairedAxisType::X);
    m_inputKeys[KeyY.GetKey()]->SetPairedAxisType(EPairedAxisType::Y);

    m_inputKeys[KeyX.GetKey()]->SetPairedAxisInputKey(InPairedKeyProxy->GetKey());
    m_inputKeys[KeyY.GetKey()]->SetPairedAxisInputKey(InPairedKeyProxy->GetKey());

    // TODO Maybe we should manage paired key proxy;

  }

  virtual int32 GetAllKeys(OUT std::vector<MInputKey>& OutKeys) const override
  {
    return -1;
  }

private:

  std::unordered_map<MInputKey, std::shared_ptr<IInputKeyProxy>> m_inputKeys;

  uint8 bIsInitialized : 1;

private:
  MInputKeyManager()
    : m_inputKeys{}
    , bIsInitialized{false}
  { }
  ~MInputKeyManager() = default;

};

IInputKeyManager& IInputKeyManager::GetInstance()
{
  return MInputKeyManager::GetInstance();
}

}

}