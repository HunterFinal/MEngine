#pragma once

#ifndef _ME_INPUTCORE_IINPUTKEY_PROXY_
#define _ME_INPUTCORE_IINPUTKEY_PROXY_

#include "CoreDefines.h"
#include "InputCoreDefines.h"
#include <iosfwd> // std::char_traits<> 

namespace std
{
  template<typename CharType, typename Traits>
  class basic_string_view;
}

using StringView = std::basic_string_view<TCHAR, std::char_traits<TCHAR>>;

namespace MEngine
{

namespace InputCore
{

enum class EPairedAxisType : uint8;
struct MInputKey;

class IInputKeyProxy
{
public:
  INPUTCORE_API virtual ~IInputKeyProxy() = default;

  INPUTCORE_API virtual bool IsModifierKey() const = 0;
  INPUTCORE_API virtual bool IsGamepadKey() const = 0;
  INPUTCORE_API virtual bool IsTouchKey() const = 0;
  INPUTCORE_API virtual bool IsMouseButtonKey() const = 0;
  INPUTCORE_API virtual bool IsAxis1D() const = 0;
  INPUTCORE_API virtual bool IsAxis2D() const = 0;
  INPUTCORE_API virtual bool IsAxis3D() const = 0;
  INPUTCORE_API virtual bool IsButtonAxis() const = 0;
  INPUTCORE_API virtual bool IsAnalogKey() const = 0;
  INPUTCORE_API virtual bool IsDigitalKey() const = 0;
  INPUTCORE_API virtual bool ShouldUpdateAxisWithoutSamples() const = 0;
  INPUTCORE_API virtual bool IsGesture() const = 0;
  INPUTCORE_API virtual bool IsDeprecated() const = 0;
  INPUTCORE_API virtual StringView GetKeyCategory() const = 0;
  INPUTCORE_API virtual StringView GetShortDisplayName() const = 0;
  INPUTCORE_API virtual StringView GetLongDisplayName() const = 0;
  INPUTCORE_API virtual EPairedAxisType GetPairedAxisType() const = 0;
  INPUTCORE_API virtual MInputKey GetPairedAxisInputKey() const = 0;
  INPUTCORE_API virtual MInputKey GetKey() const = 0;

  // TODO
  virtual void SetPairedAxisType(IN EPairedAxisType InType) { (void)InType; };
  virtual void SetPairedAxisInputKey(const MInputKey& InKey) { (void)InKey; };
};

} // namespace MEngine::InputCore

} // namespace MEngine


#endif // _ME_INPUTCORE_IINPUTKEY_PROXY_