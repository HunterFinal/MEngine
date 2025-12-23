#pragma once

#ifndef _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_
#define _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_

#include "CoreDefines.h"
#include "InputCoreDefines.h"

namespace std
{
  template<typename PointerType>
  class shared_ptr;

  template<typename T>
  class allocator;

  template<typename ContainerType, typename AllocatorType>
  class vector;
}

namespace MEngine
{

namespace InputCore
{

class IInputKeyProxy;
struct MInputKey;

class IInputKeyManager
{

public:
  static INPUTCORE_API IInputKeyManager& GetInstance();

  INPUTCORE_API virtual ~IInputKeyManager() = default;

  INPUTCORE_API virtual void Initialize() = 0;
  INPUTCORE_API virtual void AddKey(IN std::shared_ptr<IInputKeyProxy> InKeyProxy) = 0; 
  INPUTCORE_API virtual void AddPairedKey(IN std::shared_ptr<IInputKeyProxy> InPairedKeyProxy, IN const IInputKeyProxy& KeyX, IN const IInputKeyProxy& KeyY) = 0;
  INPUTCORE_API virtual std::shared_ptr<IInputKeyProxy> GetInputKeyProxy(IN const MInputKey& InKey) const = 0;
  INPUTCORE_API virtual int32 GetAllKeys(OUT std::vector<MInputKey, std::allocator<MInputKey>>& OutKeys) const = 0;
};

}

}

#endif // _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_