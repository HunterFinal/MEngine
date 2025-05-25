#pragma once

#ifndef ME_DELEGATE_INSTANCE_IMPL_FWD
#define ME_DELEGATE_INSTANCE_IMPL_FWD

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {

    /**
     * Delegate binding for regular c/c++ functions
     */
    template<typename FuncType>
    class MStaticFunctionDelegateInstance;

    /**
     * Delegate binding for struct/class member functions
     */
    template<bool IsConst, typename Class, typename FuncType>
    class MClassMethodDelegateInstance;
  }
}

#endif // ME_DELEGATE_INSTANCE_IMPL_FWD