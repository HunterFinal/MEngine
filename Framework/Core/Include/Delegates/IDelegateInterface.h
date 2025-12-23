// MEngine delegate interface
#pragma once

#ifndef ME_DELEGATE_INTERFACE
#define ME_DELEGATE_INTERFACE

#include "CoreDefines.h"
#include "Macro/CPPVerMacro.h"

/**
 * Handle to a specific delegate
 */
struct CORE_API MDelegateHandle
{
  /**
   * Delegate handle initialization protocol
   */
  enum InitProtocol
  {
    GenerateNew,
  };

  /**Null Handle with ID = 0 */
  static const MDelegateHandle NullHandle;

  /**
   * Default constructor
   * Generate an invalid handle with ID = 0
   */
  explicit CONSTEXPR MDelegateHandle()
    : m_handleID(0)
  { }

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
  friend CORE_API bool operator==(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs);

  /**
   * Check two handles for inequality
   * 
   * @param Lhs The first handle
   * @param Rhs The second handle
   * @return true if two handles have different ID, false otherwise
   */
  friend CORE_API bool operator!=(const MDelegateHandle& Lhs, const MDelegateHandle& Rhs);

  private:

    /**
     * Generate new handle ID
     * 
     * @return new handle ID that differents to another handles
     */
    static uint64 GenerateNewID();

    uint64 m_handleID;

};

namespace MEngine
{
  namespace Core
  {
    /**
     * Delegate instance interface
     */
    struct IDelegateInterface
    {
      /**
       * Destructor
       */
      virtual ~IDelegateInterface() = default;

      /**
       * Get the instance ptr that this delegate instance is bound to.
       * 
       * @return Pointer of instance,return nullptr if not bound to an instance.
       */
      virtual void* GetInstancePtr() const = 0;

      /**
       * Check if this delegate is bound to specific instance
       * 
       * @param InstancePtr Pointer of instance
       * @return true if bound to specific instance, false otherwise
       */
      virtual bool IsBoundToInstance(IN const void* InstancePtr) const = 0;

      /**
       * Checks if the instance ptr bound to this delegate instance is valid
       * 
       * @return True if the instance ptr is valid, false otherwise
       */
      virtual bool IsSafeToInvoke() const = 0;

      /**
       * Returns a handle of this delegate instance
       * 
       * @return Valid handle of this delegate instance, or invalid handle if it's not bound to any functor
       */
      virtual MDelegateHandle GetHandle() const = 0;
    };
  }
}

#endif // ME_DELEGATE_INTERFACE