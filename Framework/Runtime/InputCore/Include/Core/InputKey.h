#pragma once

#ifndef _ME_RUNTIME_INPUTCORE_INPUT_KEY_
#define _ME_RUNTIME_INPUTCORE_INPUT_KEY_

#include "IInputKeyProxy.h"

#include <memory>
#include <string>

namespace MEngine
{

namespace InputCore
{

struct MInputKeyProxy;

struct MInputKey final : public IInputKeyProxy
{
public:

  using KeyNameType = std::basic_string<TCHAR>;

  INPUTCORE_API explicit MInputKey();
  INPUTCORE_API explicit MInputKey(IN const KeyNameType& InKeyName);
  INPUTCORE_API explicit MInputKey(IN const TCHAR* InKeyName);
  INPUTCORE_API virtual ~MInputKey();

  /**Start IInputKeyProxy interface */
  INPUTCORE_API bool IsModifierKey() const override final;
  INPUTCORE_API bool IsGamepadKey() const override final;
  INPUTCORE_API bool IsTouchKey() const override final;
  INPUTCORE_API bool IsMouseButtonKey() const override final;
  INPUTCORE_API bool IsAxis1D() const override final;
  INPUTCORE_API bool IsAxis2D() const override final;
  INPUTCORE_API bool IsAxis3D() const override final;
  INPUTCORE_API bool IsButtonAxis() const override final;
  INPUTCORE_API bool IsAnalogKey() const override final;
  INPUTCORE_API bool IsDigitalKey() const override final;
  INPUTCORE_API bool ShouldUpdateAxisWithoutSamples() const override final;
  INPUTCORE_API bool IsGesture() const override final;
  INPUTCORE_API bool IsDeprecated() const override final;
  INPUTCORE_API StringView GetKeyCategory() const override final;
  INPUTCORE_API StringView GetShortDisplayName() const override final;
  INPUTCORE_API StringView GetLongDisplayName() const override final;
  INPUTCORE_API EPairedAxisType GetPairedAxisType() const override final;
  INPUTCORE_API MInputKey GetPairedAxisInputKey() const override final;
  INPUTCORE_API MInputKey GetKey() const override final;

  void SetPairedAxisType(IN EPairedAxisType InType) override final;
  void SetPairedAxisInputKey(IN const MInputKey& InKey) override final;
  /**End IInputKeyProxy interface */

  INPUTCORE_API bool IsValid() const;
  INPUTCORE_API StringView GetKeyName() const;

  INPUTCORE_API friend bool operator==(IN const MInputKey& Lhs,IN const MInputKey& Rhs);
  INPUTCORE_API friend bool operator!=(IN const MInputKey& Lhs,IN const MInputKey& Rhs);

private:
  void Reset();
  void ConditionalLookupProxy() const;

private:
  mutable std::shared_ptr<IInputKeyProxy> m_proxy;

  KeyNameType m_keyName;
};

} // namespace MEngine::InputCore

} // namespace MEngine

#endif // _ME_RUNTIME_INPUTCORE_INPUT_KEY_