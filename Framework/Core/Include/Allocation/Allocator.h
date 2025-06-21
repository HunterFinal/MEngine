#pragma once

#ifndef _ME_CORE_ALLOCATOR_
#define _ME_CORE_ALLOCATOR_

#include "Macro/AssertionMacros.h"
#include "Misc/CoreDefines.h"

#include <limits>
#include <type_traits>

#if CAN_USE_CONCEPT
  template<typename ElementType>
  concept AllocatorConcept = requires
  {
    requires !std::is_void_v<typename std::remove_pointer_t<ElementType>>;
  };
#endif

namespace MEngine
{
  namespace Core
  {
    // TODO Need more research
    // TODO use this as Allocator element header ptr instead of void*
    struct AllocatorElement
    {};

    #if CAN_USE_CONCEPT
      template<AllocatorConcept ElementType>
    #else
      template<typename ElementType>
    #endif
    struct DefaultAllocator final
    {
      #if !CAN_USE_CONCEPT
        static_assert(!std::is_void<std::remove_pointer<ElementType>::type>::value, "Can't use void or void* as element type of Allocator");
      #endif
      explicit DefaultAllocator()
        : m_data(nullptr)
      { }

      ~DefaultAllocator()
      {
        Deallocate();
      }

      DefaultAllocator(IN DefaultAllocator&& Other) noexcept
        : m_data(Other.m_data)
      {
        Other.m_data = nullptr;
      }

      DefaultAllocator& operator=(IN DefaultAllocator&& Other) noexcept
      {
        if (this != &Other)
        {
          if (m_data != nullptr)
          {
            ::free(m_data);
          }

          m_data = Other.m_data;
          Other.m_data = nullptr;
        }

        return *this;
      }

      void Allocate(IN SIZE_T ElementNum, IN SIZE_T ByteSizePerElement)
      {
        // overflow check
        bool bInvalidAlloc = (ByteSizePerElement < static_cast<SIZE_T>(1)) || (ByteSizePerElement > static_cast<SIZE_T>(std::numeric_limits<int32>::max()));
        me_assert(!bInvalidAlloc);

        // TODO m_data == nullptr: same as ::malloc(ElementNum * ByteSizePerElement);
        // TODO (ElementNum * ByteSizePerElement == 0) || (m_data != nullptr): free(m_data) first and return nullptr; 
        m_data = reinterpret_cast<AllocatorElement*>(::realloc(m_data, ElementNum * ByteSizePerElement));
      }

      void Deallocate()
      {
        if (m_data != nullptr)
        {
          // can not use delete because size is different
          ::free(m_data);
          m_data = nullptr;
        }
      }

      ElementType* GetAllocation() const
      {
        return reinterpret_cast<ElementType*>(m_data);
      }

      bool HasAllocation() const
      {
        return !!m_data;
      }

      private:
        AllocatorElement* m_data;

      /**
       * Uncopyable
       */
      public:
        DefaultAllocator(IN const DefaultAllocator& Other) = delete;
        DefaultAllocator& operator=(IN const DefaultAllocator& Other) = delete;
    };
  }
}

#endif // _ME_CORE_ALLOCATOR_