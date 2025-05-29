#pragma once

#ifndef ME_CORE_ALLOCATOR
#define ME_CORE_ALLOCATOR

#include "HAL/Platform.h"
#include "Misc/CoreDefines.h"
#include <cassert>
#include <limits>
#include <type_traits>

namespace MEngine
{
  namespace Core
  {
    // TODO Need more research
    // use this as Allocator element header ptr instead of void*
    struct AllocatorElement
    {};

    template<typename ElementType>
    struct DefaultAllocator;

    template<typename ElementType>
    struct DefaultAllocator final
    {
      static_assert(!std::is_void<std::remove_pointer<ElementType>::type>::value, "Can't use void or void* as element type of Allocator");

      explicit DefaultAllocator()
        : m_data(nullptr)
      { }

      ~DefaultAllocator()
      {
        Deallocate();
      }

      DefaultAllocator(DefaultAllocator&& Other) noexcept
        : m_data(Other.m_data)
      {
        Other.m_data = nullptr;
      }

      DefaultAllocator& operator=(DefaultAllocator&& Other) noexcept
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
        bool bInvalidAlloc = (ByteSizePerElement < 1) || (ByteSizePerElement > std::numeric_limits<int32>::max());
        assert(!bInvalidAlloc);

        // TODO
        // m_data == nullptr: same as ::malloc(ElementNum * ByteSizePerElement);
        // (ElementNum * ByteSizePerElement == 0) || (m_data != nullptr): free(m_data) first and return nullptr; 
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
        DefaultAllocator(const DefaultAllocator& Other) = delete;
        DefaultAllocator& operator=(const DefaultAllocator& Other) = delete;
    };
  }
}


#endif // ME_CORE_ALLOCATOR