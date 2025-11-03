#include "Core/InputKeyProxy.h"
#include "Core/InputKey.h"
#include "Globals/KeyGlobals.h"
#include "InputCoreAPI.h"

#include "Macro/AssertionMacros.h"

#include <memory>

namespace
{
  // NOTE: From Unreal engine
  // TODO Need more research
  enum EInputAxisType : uint8
  {
    None,
    Button,       // Whilst the physical input is an analog axis the FKey uses it to emulate a digital button.
    Axis1D,
    Axis2D,
    Axis3D,
  };
}

namespace MEngine
{

namespace InputCore
{
  struct MInputKeyProxy::InternalData
  {
    public:
      InternalData(IN const MInputKey& InInputKey, IN StringView InLongDisplayName, IN StringView InShortDisplayName, IN StringView InKeyCategory)
        : Key{InInputKey}
        , PairedKey{GStaticKeys::Invalid}
        , KeyCategoryName{InKeyCategory}
        , ShortDisplayName{InShortDisplayName}
        , LongDisplayName{InLongDisplayName}
        , InputAxisType{EInputAxisType::None}
        , PairedKeyAxisType{EPairedAxisType::Unpaired}
      { }

    public:
      MInputKey Key;
      MInputKey PairedKey;
      MInputKey::KeyNameType KeyCategoryName;
      MInputKey::KeyNameType ShortDisplayName;
      MInputKey::KeyNameType LongDisplayName;
      EInputAxisType InputAxisType;
      EPairedAxisType PairedKeyAxisType;
  };

  MInputKeyProxy::MInputKeyProxy(IN const MInputKey& InInputKey, IN StringView InLongDisplayName, IN StringView InShortDisplayName, IN StringView InKeyCategory, IN uint32 InKeyFlags)
    : m_pImplData{std::make_unique<MInputKeyProxy::InternalData>(InInputKey, InLongDisplayName, InShortDisplayName, InKeyCategory)}
  {
    me_assert(m_pImplData != nullptr);
    InitializeInternal(InKeyFlags);
  }

  MInputKeyProxy::~MInputKeyProxy() = default;

  void MInputKeyProxy::InitializeInternal(IN const uint32 InKeyFlags)
  {
    // Initialize flags
    bIsModifierKey = (InKeyFlags & ModifierKey) != EKeyFlags::None;
    bIsGamepadKey = (InKeyFlags & GamepadKey) != EKeyFlags::None;
    bIsTouchKey = (InKeyFlags & TouchKey) != EKeyFlags::None;
    bIsMouseButtonKey = (InKeyFlags & MouseButtonKey) != EKeyFlags::None;
    bShouldUpdateAxisWithoutSamples = (InKeyFlags & UpdateAxisWithoutSamples) != EKeyFlags::None;
    bIsGesture = (InKeyFlags & Gesture) != EKeyFlags::None;
    bIsDeprecated = (InKeyFlags & Deprecated) != EKeyFlags::None;

    // Initialize Axis type
    if ((InKeyFlags & EKeyFlags::ButtonAxis) != EKeyFlags::None)
    {
      me_assert((InKeyFlags & (EKeyFlags::Axis1D | EKeyFlags::Axis2D | EKeyFlags::Axis3D)) == EKeyFlags::None);
      m_pImplData->InputAxisType = EInputAxisType::Button;
    }
    else if ((InKeyFlags & EKeyFlags::Axis1D) != EKeyFlags::None)
    {
      me_assert((InKeyFlags & (EKeyFlags::Axis2D | EKeyFlags::Axis3D)) == EKeyFlags::None);
      m_pImplData->InputAxisType = EInputAxisType::Axis1D;
    }
    else if ((InKeyFlags & EKeyFlags::Axis2D) != EKeyFlags::None)
    {
      me_assert((InKeyFlags & EKeyFlags::Axis3D) == EKeyFlags::None);
      m_pImplData->InputAxisType = EInputAxisType::Axis2D;
    }
    else if ((InKeyFlags & EKeyFlags::Axis3D) != EKeyFlags::None)
    {
      m_pImplData->InputAxisType = EInputAxisType::Axis3D;
    }
    else 
    {
      m_pImplData->InputAxisType = EInputAxisType::None;
    }

    // Initialize key category
    if (GetKeyCategory() == INVALID_KEY_CATEGORY || GetKeyCategory().empty())
    {
      if (IsGamepadKey())
      {
        m_pImplData->KeyCategoryName = NAME_GAMEPAD_CATEGORY;
      }
      else if (IsMouseButtonKey())
      {
        m_pImplData->KeyCategoryName = NAME_MOUSE_CATEGORY;
      }
      else
      {
        m_pImplData->KeyCategoryName = NAME_KEYBOARD_CATEGORY;
      }
    }
  }

  bool MInputKeyProxy::IsModifierKey() const
  {
    return bIsModifierKey;
  }

  bool MInputKeyProxy::IsGamepadKey() const
  {
    return bIsGamepadKey;
  }

  bool MInputKeyProxy::IsTouchKey() const
  {
    return bIsTouchKey;
  }

  bool MInputKeyProxy::IsMouseButtonKey() const
  {
    return bIsMouseButtonKey;
  }

  bool MInputKeyProxy::IsAxis1D() const
  {
    return m_pImplData->InputAxisType == EInputAxisType::Axis1D;
  }

  bool MInputKeyProxy::IsAxis2D() const
  {
    return m_pImplData->InputAxisType == EInputAxisType::Axis2D;
  }

  bool MInputKeyProxy::IsAxis3D() const
  {
    return m_pImplData->InputAxisType == EInputAxisType::Axis3D;
  }

  bool MInputKeyProxy::IsButtonAxis() const
  {
    return m_pImplData->InputAxisType == EInputAxisType::Button;
  }

  bool MInputKeyProxy::IsAnalogKey() const
  {
    const bool bResult = IsAxis1D() || IsAxis2D() || IsAxis3D();
    return bResult;
  }

  bool MInputKeyProxy::IsDigitalKey() const
  {
    return !IsAnalogKey();
  }

  bool MInputKeyProxy::ShouldUpdateAxisWithoutSamples() const
  {
    return bShouldUpdateAxisWithoutSamples;
  }

  bool MInputKeyProxy::IsGesture() const
  {
    return bIsGesture;
  }

  bool MInputKeyProxy::IsDeprecated() const
  {
    return bIsDeprecated;
  }

  StringView MInputKeyProxy::GetKeyCategory() const
  {
    return m_pImplData->KeyCategoryName;
  }

  StringView MInputKeyProxy::GetShortDisplayName() const
  {
    return !m_pImplData->ShortDisplayName.empty() ? m_pImplData->ShortDisplayName : GetLongDisplayName();
  }

  StringView MInputKeyProxy::GetLongDisplayName() const
  {
    return m_pImplData->LongDisplayName;
  }

  EPairedAxisType MInputKeyProxy::GetPairedAxisType() const
  {
    return m_pImplData->PairedKeyAxisType;
  }

  MInputKey MInputKeyProxy::GetPairedAxisInputKey() const
  {
    return m_pImplData->PairedKey; 
  }

  MInputKey MInputKeyProxy::GetKey() const
  {
    return m_pImplData->Key;
  }
  
  void MInputKeyProxy::SetPairedAxisType(IN EPairedAxisType InType)
  {
    m_pImplData->PairedKeyAxisType = InType;
  }

  void MInputKeyProxy::SetPairedAxisInputKey(const MInputKey& InKey)
  {
    m_pImplData->PairedKey = InKey;
  }
} // namespace MEngine::InputCore

} // namespace MEngine

