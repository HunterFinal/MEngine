#pragma once

#ifndef _ME_CORE_MEMORYMANAGEMENT_
#define _ME_CORE_MEMORYMANAGEMENT_

#include "CoreDefines.h"

namespace MEngine
{

namespace Core
{

struct MemChunkStack final
{
  struct ChunkHeader
  {
    ChunkHeader* Next;
    SIZE_T Size;
    SIZE_T UsedSize;

    FORCEINLINE uint8* Top() const
    {
      return const_cast<uint8*>(reinterpret_cast<const uint8*>(this) + sizeof(ChunkHeader) + UsedSize);
    }

    FORCEINLINE uint8* End() const
    {
      return const_cast<uint8*>(reinterpret_cast<const uint8*>(this) + sizeof(ChunkHeader) + Size);
    }

    FORCEINLINE SIZE_T Remaining() const
    {
      return Size - UsedSize;
    }
  };

  public:
    CORE_API MemChunkStack();
    CORE_API ~MemChunkStack();

    MemChunkStack(IN MemChunkStack&& Other)
    {
      *this = std::move(Other);
    }
    CORE_API MemChunkStack& operator=(IN MemChunkStack&& Other);

    CORE_API void* Allocate(IN SIZE_T AllocSize, IN SIZE_T Alignment);

    CORE_API bool IsEmpty() const;
    
    MemChunkStack(IN const MemChunkStack& Other) = delete;
    MemChunkStack& operator=(IN const MemChunkStack& Other) = delete;

  private:
    void AllocateNewChunk(IN SIZE_T MinSize);
    void FreeChunks(IN ChunkHeader* NewTopChunkHeader);

  private:
    ChunkHeader* m_topChunkHeader;

};

}

}


#endif // _ME_CORE_MEMORYMANAGEMENT_



