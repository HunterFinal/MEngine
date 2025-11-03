#pragma once

#ifndef _ME_RUNTIME_INPUTCORE_INTERNAL_IINPUTPROXYFACTORY_
#define _ME_RUNTIME_INPUTCORE_INTERNAL_IINPUTPROXYFACTORY_

#include "Internal/InputCoreDefines.h"
#include "IInputKeyProxy.h"

#include <memory>

namespace MEngine
{

namespace InputCore
{

class MInputKey;

class IInputProxyFactory
{
public:
  INPUTCORE_API virtual ~IInputProxyFactory() = default;

  INPUTCORE_API virtual std::shared_ptr<IInputKeyProxy> MakeInputKeyProxy(IN const MInputKey InInputKey, IN StringView InLongDisplayName, IN const uint32 InKeyFlags = 0, IN StringView InShortDisplayName = StringView{}, IN StringView InKeyCategory = StringView{}) const = 0;
};

}

}

#endif // _ME_RUNTIME_INPUTCORE_INTERNAL_IINPUTPROXYFACTORY_