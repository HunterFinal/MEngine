// MEngine delegate interface
#pragma once

#ifndef ME_DELEGATE_INTERFACE
#define ME_DELEGATE_INTERFACE

#include "HAL/Platform.h"
#include "Misc/CoreDefines.h"
#include "Macro/CPPVerMacro.h"

namespace MEngine
{
  namespace Core
  {
    /**
     * Handle to a specific delegate
     */
    struct MDelegateHandle
    {
      /**
       * Delegate handle initialization protocol
       */
      enum InitProtocol
      {
        GenerateNew,
      };

      #if HAS_CPP_17
        static constexpr MDelegateHandle NullHandle = MDelegateHandle{};
      #else
        static const MDelegateHandle;
      #endif

      /**
       * Default constructor
       * Generate an invalid handle
       */
      MDelegateHandle();

      /**
       * Constructor that use protocol
       * 
       * @param Protocol Initialization protocol
       */
      explicit MDelegateHandle(InitProtocol Protocol); 

      /**
       * Check if this handle is binding a valid delegate
       * 
       * @return true if is binding a valid delegate, false otherwise
       */
      bool IsValid() const;

      /**
       * Clear handle to indicate it is no longer bound delegate
       */
      void Reset();

      /**
       * Check two handles for equality
       * 
       * @param Lhs The first handle
       * @param Rhs The second handle
       * @return true if two handles have same ID, false otherwise
       */
      friend bool operator==(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs);

      /**
       * Check two handles for inequality
       * 
       * @param Lhs The first handle
       * @param Rhs The second handle
       * @return true if two handles have different ID, false otherwise
       */
      friend bool operator!=(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs);

      private:

        /**
         * Generate new handle ID
         * 
         * @return new handle ID that differents to another handles
         */
        static uint64 GenerateNewID();

        uint64 m_handleID;

    };

  }
}

bool operator==(const MEngine::Core::MDelegateHandle& Lhs, const MEngine::Core::MDelegateHandle& Rhs);
bool operator!=(const MEngine::Core::MDelegateHandle& Lhs, const MEngine::Core::MDelegateHandle& Rhs);

#endif // ME_DELEGATE_INTERFACE