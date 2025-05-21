// MEngine Logger

#pragma once

#ifndef ME_CORE_OUTPUT_INTERFACE
#define ME_CORE_OUTPUT_INTERFACE

// TODO
#include "HAL/Platform.h"

#include "Misc/CoreDefines.h"

namespace MEngine
{
  namespace Core
  {
    struct CORE_API IOutputInterface
    {
      public:
        IOutputInterface() = default;
        virtual ~IOutputInterface() = 0 { };
      
      /**
       * Not copyable and not moveable
       */
      IOutputInterface(const IOutputInterface&) = delete;
      IOutputInterface& operator=(const IOutputInterface&) = delete;
      IOutputInterface(IOutputInterface&&) noexcept = delete;
      IOutputInterface& operator=(IOutputInterface&&) noexcept = delete;

      /**
       * Start up output 
       */
      virtual void Startup() { };
      /**
       * Terminate output
       */
      virtual void Terminate() { };
      /**
       * Serialize data and output to device
       * 
       * @param Data String data to serialize
       */
      virtual void Serialize(IN const ANSICHAR* Data) { };
      /**
       * Flush data stacking in buffer
       */
      virtual void Flush() { };

      #ifdef TEST_PHASE
        virtual void Serialize_Debug(const ANSICHAR* Data) {};
      #endif

    }; 
  }
}

#endif // ME_CORE_OUTPUT_INTERFACE