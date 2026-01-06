/**
 * @file Allocator.h
 * @author MAI ZHICONG
 * @brief Default allocator for heap memory management
 * @version 0.1
 * @date 2025-10-14
 * 
 * @copyright Copyright (c) 2025~2025 MAI ZHICONG
 */

#pragma once

#ifndef _ME_CORE_ALLOCATOR_
#define _ME_CORE_ALLOCATOR_

#include "CoreDefines.h"
#include "Macro/AssertionMacros.h"
#include "Misc/ConceptsStoragePlace.h"

#include <limits>

namespace MEngine
{
  
namespace Core
{
// TODO use this as Allocator element header ptr instead of void*

template<ALLOCATOR_TYPE_CONCEPT ElementType>
struct DefaultAllocator final
{
  #if !CAN_USE_CONCEPT
    static_assert(sizeof(ElementType) > 0, "Can't use incomplete type or void as element of Allocator");
  #endif

  /**
   * Constructors, destructor and assignment
   */
  DefaultAllocator();
  ~DefaultAllocator();
  DefaultAllocator(IN DefaultAllocator&& Other) noexcept;
  DefaultAllocator& operator=(IN DefaultAllocator&& Other) noexcept;

  /**
   * @brief Allocate desire memory
   * 
   *        ほしい分のメモリを確保する
   * 
   * @param ElementNum Num of required element
   * 
   * 確保する要素の数
   * 
   * @param ByteSizePerElement Memory size(unit : byte) that each element need
   * 
   * 各要素のほしいメモリサイズ（バイト単位）
   * 
   */
  void Allocate(IN SIZE_T ElementNum, IN SIZE_T ByteSizePerElement);

  /**
   * @brief Deallocate element/elements
   * 
   * 確保した要素を解放する
   */
  void Deallocate();

  /**
   * @brief Get allocated memory address
   * 
   * 要素を取得
   * 
   * @return Pointer of allocated memory, nullptr if this is not allocated
   * 
   * 確保した領域の先頭アドレスを返す、確保していないとnullptrを返す 
   */
  ElementType* GetAllocation() const;

  /**
   * @brief Check if memory is allocated
   * 
   * 要素を確保したかを確認
   * 
   * @return True if memory is allocated, false otherwise
   * 
   * 確保したらtrueを返す、それ以外はfalseを返す
   */
  bool HasAllocation() const;

  private:
    uint8* m_data;

  /**
   * Uncopyable
   */
  public:
    DefaultAllocator(IN const DefaultAllocator& Other) = delete;
    DefaultAllocator& operator=(IN const DefaultAllocator& Other) = delete;
};

#pragma region Default allocator def
#define TEMPLATE_HEADER(Typename) template<ALLOCATOR_TYPE_CONCEPT Typename> 

TEMPLATE_HEADER(ElementType)
DefaultAllocator<ElementType>::DefaultAllocator()
  : m_data{nullptr}
{}

TEMPLATE_HEADER(ElementType)
DefaultAllocator<ElementType>::~DefaultAllocator()
{
  Deallocate();
}

TEMPLATE_HEADER(ElementType)
DefaultAllocator<ElementType>::DefaultAllocator(IN DefaultAllocator&& Other) noexcept
  : m_data(Other.m_data)
{
  Other.m_data = nullptr;
}

TEMPLATE_HEADER(ElementType)
DefaultAllocator<ElementType>& DefaultAllocator<ElementType>::operator=(IN DefaultAllocator<ElementType>&& Other) noexcept
{
  if (this != &Other)
  {
    Deallocate();

    m_data = Other.m_data;
    Other.m_data = nullptr;
  }

  return *this;
}

TEMPLATE_HEADER(ElementType)
void DefaultAllocator<ElementType>::Allocate(IN SIZE_T ElementNum, IN SIZE_T ByteSizePerElement)
{
  // overflow check
  const bool bInvalidAlloc = (ByteSizePerElement < static_cast<SIZE_T>(1)) || (ByteSizePerElement > static_cast<SIZE_T>(std::numeric_limits<int32>::max()));
  me_assert(!bInvalidAlloc);

  // TODO m_data == nullptr: same as ::malloc(ElementNum * ByteSizePerElement);
  // TODO (ElementNum * ByteSizePerElement == 0) && (m_data != nullptr): free(m_data) first and return nullptr; 
  m_data = reinterpret_cast<uint8*>(
            ::realloc(m_data, ElementNum * ByteSizePerElement)
          );
}

TEMPLATE_HEADER(ElementType)
void DefaultAllocator<ElementType>::Deallocate()
{
  if (m_data != nullptr)
  {
    // can not use delete because size is different
    ::free(m_data);
    m_data = nullptr;
  }
}

TEMPLATE_HEADER(ElementType)
ElementType* DefaultAllocator<ElementType>::GetAllocation() const
{
  return reinterpret_cast<ElementType*>(m_data);
}

TEMPLATE_HEADER(ElementType)
bool DefaultAllocator<ElementType>::HasAllocation() const
{
  return !!m_data;
}

#undef TEMPLATE_HEADER
#pragma endregion Default allocator def

} // namespace MEngine::Core

} // namespace MEngine

#endif // _ME_CORE_ALLOCATOR_