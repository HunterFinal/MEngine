// MEngine Logger

#pragma once

#ifndef ME_CORE_OUTPUT_INTERFACE
#define ME_CORE_OUTPUT_INTERFACE

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    struct CORE_API IOutputInterface
    {
      public:
        IOutputInterface() = default;
        virtual ~IOutputInterface() = default;
      
      /**
       * Not copyable and not moveable
       */
      IOutputInterface(const IOutputInterface&) = delete;
      IOutputInterface& operator=(const IOutputInterface&) = delete;
      IOutputInterface(IOutputInterface&&) noexcept = delete;
      IOutputInterface& operator=(IOutputInterface&&) noexcept = delete;

      virtual void Startup() = 0;
      virtual void Terminate() = 0;
      virtual void Serialize(const ANSICHAR* Data) = 0;

    }; 
  }
}

#endif // ME_CORE_OUTPUT_INTERFACE