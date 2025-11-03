#pragma once

#ifndef _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_
#define _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_

#include "Misc/CoreDefines.h"
#include "Internal/InputCoreDefines.h"

namespace std
{
  template<typename PointerType>
  class shared_ptr;

  template<typename ContainerType>
  class vector;
}

namespace MEngine
{

namespace InputCore
{

class IInputKeyProxy;
class MInputKey;

class IInputKeyManager
{

public:
  static INPUTCORE_API IInputKeyManager& GetInstance();

  INPUTCORE_API virtual ~IInputKeyManager() = default;

  INPUTCORE_API virtual void Initialize() = 0;
  INPUTCORE_API virtual void AddKey(IN std::shared_ptr<IInputKeyProxy> InKeyProxy) = 0; 
  INPUTCORE_API virtual void AddPairedKey(IN std::shared_ptr<IInputKeyProxy> InPairedKeyProxy, IN const IInputKeyProxy& KeyX, IN const IInputKeyProxy& KeyY) = 0;
  INPUTCORE_API virtual int32 GetAllKeys(OUT std::vector<MInputKey>& OutKeys) const = 0;
};

}

}

#endif // _ME_RUNTIME_INPUTCORE_IINPUTKEYMANAGER_