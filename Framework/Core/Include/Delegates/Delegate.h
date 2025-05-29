#pragma once

#ifndef ME_DELEGATE_USECASE
#define ME_DELEGATE_USECASE

#include "Macro/TypeAliasMacro.h"

#include "Delegates/DelegateImpl.h"
#include "Delegates/DelegateInstanceImpl.h"
#include "Delegates/DelegateInstanceImplFwd.h"
#include "Delegates/MulticastDelegateImpl.h"

// Delegate alias (c# style)
template<typename FuncType> TYPEDEF(MEngine::Core::MMulticastDelegate<FuncType>, MAction);
template<typename FuncType> TYPEDEF(MEngine::Core::MDelegate<FuncType>, MDelegate);

#endif // ME_DELEGATE_USECASE