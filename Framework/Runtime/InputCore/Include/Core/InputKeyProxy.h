#pragma once

#ifndef _ME_INPUTCORE_INPUT_KEY_PROXY_
#define _ME_INPUTCORE_INPUT_KEY_PROXY_

#include "IInputKeyProxy.h"
#include "Macro/BitOperationMacros.h"

#include <memory>

namespace MEngine
{

namespace InputCore
{

struct MInputKeyProxy final : public IInputKeyProxy
{

public:
  enum EKeyFlags : uint32
  {
    ModifierKey              = BIT_FLAG(0),
    GamepadKey               = BIT_FLAG(1),
    TouchKey                 = BIT_FLAG(2),
    MouseButtonKey           = BIT_FLAG(3),
    Axis1D                   = BIT_FLAG(4),
    Axis2D                   = BIT_FLAG(5),
    Axis3D                   = BIT_FLAG(6),
    ButtonAxis               = BIT_FLAG(7),
    UpdateAxisWithoutSamples = BIT_FLAG(8),
    Gesture                  = BIT_FLAG(9),
    Deprecated               = BIT_FLAG(10),

    None                     = 0,
  };

public:
  explicit MInputKeyProxy(IN const MInputKey& InInputKey, IN StringView InLongDisplayName, IN StringView InShortDisplayName, IN StringView InKeyCategory, IN uint32 InKeyFlags = 0);
  virtual ~MInputKeyProxy();

  /**Start IInputKeyProxy interface */
  bool IsModifierKey() const override final;
  bool IsGamepadKey() const override final;
  bool IsTouchKey() const override final;
  bool IsMouseButtonKey() const override final;
  bool IsAxis1D() const override final;
  bool IsAxis2D() const override final;
  bool IsAxis3D() const override final;
  bool IsButtonAxis() const override final;
  bool IsAnalogKey() const override final;
  bool IsDigitalKey() const override final;
  bool ShouldUpdateAxisWithoutSamples() const override final;
  bool IsGesture() const override final;
  bool IsDeprecated() const override final;
  StringView GetKeyCategory() const override final;
  StringView GetShortDisplayName() const override final;
  StringView GetLongDisplayName() const override final;
  EPairedAxisType GetPairedAxisType() const override final;
  MInputKey GetPairedAxisInputKey() const override final;
  MInputKey GetKey() const override final;

  void SetPairedAxisType(IN EPairedAxisType InType) override final;
  void SetPairedAxisInputKey(const MInputKey& InKey) override final;
  /**End IInputKeyProxy interface */


private:
  void InitializeInternal(IN const uint32 InKeyFlags);

private:
  struct InternalData;
  std::unique_ptr<InternalData> m_pImplData;

  uint8 bIsModifierKey : 1;
  uint8 bIsGamepadKey : 1;
  uint8 bIsTouchKey : 1;
  uint8 bIsMouseButtonKey : 1;
  uint8 bShouldUpdateAxisWithoutSamples : 1;
  uint8 bIsGesture : 1;
  uint8 bIsDeprecated : 1;

public:
  /**Disable copy and move */
  MInputKeyProxy(const MInputKeyProxy& Other) = delete;
  MInputKeyProxy& operator=(const MInputKeyProxy& Other) = delete;
  MInputKeyProxy(MInputKeyProxy&& Other) noexcept = delete;
  MInputKeyProxy& operator=(MInputKeyProxy&& Other) noexcept = delete;

}; // struct MInputKeyProxy

} // namespace MEngine::InputCore 

} // namespace MEngine

#endif // _ME_INPUTCORE_INPUT_KEY_PROXY_