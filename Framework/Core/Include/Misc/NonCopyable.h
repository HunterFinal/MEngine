#pragma once

#ifndef _ME_CORE_NONCOPYABLE_
#define _ME_CORE_NONCOPYABLE_

#include "Macro/TypeAliasMacro.h"

namespace MEngine
{
  namespace Core
  {
    /**
     * @brief Non-copyable base class
     */
    struct MNonCopyableImpl
    {
      MNonCopyableImpl() = default;
      virtual ~MNonCopyableImpl() = default;

      MNonCopyableImpl(const MNonCopyableImpl&) = delete;
      MNonCopyableImpl& operator=(const MNonCopyableImpl&) = delete;
      MNonCopyableImpl(MNonCopyableImpl&&) noexcept = default;
      MNonCopyableImpl& operator=(MNonCopyableImpl&&) noexcept = default;
    };
  }
}

TYPEDEF(MEngine::Core::MNonCopyableImpl, MNonCopyable);

#endif // _ME_CORE_NONCOPYABLE_