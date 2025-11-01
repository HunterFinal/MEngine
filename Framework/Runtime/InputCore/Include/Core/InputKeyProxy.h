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
    Button                   = BIT_FLAG(7),
    UpdateAxisWithoutSamples = BIT_FLAG(8),
    Gesture                  = BIT_FLAG(9),
    Deprecated               = BIT_FLAG(10),

    None                     = 0,
  };

public:
  INPUTCORE_API MInputKeyProxy(IN const MInputKey& InInputKey, IN StringView InLongDisplayName, IN StringView InShortDisplayName, IN StringView InKeyCategory, IN uint32 InKeyFlags = 0);
  INPUTCORE_API virtual ~MInputKeyProxy();

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
  /**End IInputKeyProxy interface */

  INPUTCORE_API MInputKey GetKey() const;

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