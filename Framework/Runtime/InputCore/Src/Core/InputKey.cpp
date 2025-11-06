#include "Core/InputKey.h"

#include "InputCoreAPI.h"

#include <string_view>

namespace MEngine
{

namespace InputCore
{
  MInputKey::MInputKey()
    : m_proxy{nullptr}
    , m_keyName{INVALID_KEY_NAME}
  { }

  MInputKey::MInputKey(IN const KeyNameType& InKeyName)
    : m_proxy{nullptr}
    , m_keyName{InKeyName}
  { }

  MInputKey::MInputKey(IN const TCHAR* InKeyName)
    : m_proxy{nullptr}
    , m_keyName{InKeyName}
  { }

  MInputKey::~MInputKey() = default;

  bool MInputKey::IsModifierKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsModifierKey() : false;
  }

  bool MInputKey::IsGamepadKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsGamepadKey() : false;
  }

  bool MInputKey::IsTouchKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsTouchKey() : false;
  }

  bool MInputKey::IsMouseButtonKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsMouseButtonKey() : false;
  }

  bool MInputKey::IsAxis1D() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsAxis1D() : false;
  }

  bool MInputKey::IsAxis2D() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsAxis2D() : false;
  }

  bool MInputKey::IsAxis3D() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsAxis3D() : false;
  }
  
  bool MInputKey::IsButtonAxis() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsButtonAxis() : false;
  }

  bool MInputKey::IsAnalogKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsAnalogKey() : false;
  }
  
  bool MInputKey::IsDigitalKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsDigitalKey() : false;
  }

  bool MInputKey::ShouldUpdateAxisWithoutSamples() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->ShouldUpdateAxisWithoutSamples() : false;
  }

  bool MInputKey::IsGesture() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsGesture() : false;
  }

  bool MInputKey::IsDeprecated() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->IsDeprecated() : false;
  }

  StringView MInputKey::GetKeyCategory() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetKeyCategory() : StringView{NAME_KEYBOARD_CATEGORY};
  }

  StringView MInputKey::GetShortDisplayName() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetShortDisplayName() : StringView{m_keyName};
  }

  StringView MInputKey::GetLongDisplayName() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetLongDisplayName() : StringView{m_keyName};
  }

  EPairedAxisType MInputKey::GetPairedAxisType() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetPairedAxisType() : EPairedAxisType::Unpaired;
  }
  
  MInputKey MInputKey::GetPairedAxisInputKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetPairedAxisInputKey() : GStaticKeys::Invalid;    
  }

  MInputKey MInputKey::GetKey() const
  {
    ConditionalLookupProxy();
    return (m_proxy != nullptr) ? m_proxy->GetPairedAxisInputKey() : *this;
  }

  void MInputKey::SetPairedAxisType(IN EPairedAxisType InType)
  {
    ConditionalLookupProxy();
    if (m_proxy != nullptr)
    {
      m_proxy->SetPairedAxisType(InType);
    }
  }

  void MInputKey::SetPairedAxisInputKey(const MInputKey& InKey)
  {
    ConditionalLookupProxy();
    if (m_proxy != nullptr)
    {
      m_proxy->SetPairedAxisInputKey(InKey);
    }
  }

  bool MInputKey::IsValid() const
  {
    if (m_keyName != INVALID_KEY_NAME)
    {
      ConditionalLookupProxy();
      return m_proxy != nullptr;
    }

    return false;
  }

  StringView MInputKey::GetKeyName() const
  {
    return m_keyName;
  }

  void MInputKey::Reset()
  {
    m_proxy = nullptr;
  }

  void MInputKey::ConditionalLookupProxy() const
  {
    if (m_proxy == nullptr)
    {
      IInputKeyManager& inputKeyManager = IInputKeyManager::GetInstance();
      m_proxy = inputKeyManager.GetInputKeyProxy(*this);
    }
  }

bool operator==(const MInputKey& Lhs, const MInputKey& Rhs)
{
  return Lhs.m_keyName == Rhs.m_keyName;
}

bool operator!=(const MInputKey& Lhs, const MInputKey& Rhs)
{
  return !(Lhs == Rhs);
}

} // namespace MEngine::InputCore

} // namespace MEngine
