#include "Memory/MemoryManagement.h"
#include "Macro/AssertionMacros.h"
#include "Templates/AlignmentUtils.h"

namespace MEngine
{

namespace Core
{

MemChunkStack::MemChunkStack()
  : m_topChunkHeader{nullptr}
{}

MemChunkStack::~MemChunkStack()
{
  // Free all memory blocks
  FreeChunks(nullptr);
}

MemChunkStack& MemChunkStack::operator=(IN MemChunkStack&& Other)
{
  if (&Other != this)
  {
    this->FreeChunks(nullptr);
    m_topChunkHeader = Other.m_topChunkHeader;

    Other.m_topChunkHeader = nullptr;
  }

  return *this;
}

void* MemChunkStack::Allocate(IN SIZE_T AllocSize, IN SIZE_T Alignment)
{
  me_assert(AllocSize >= 0);
  // Alignment must be power of 2
  me_assert((Alignment & (Alignment - 1)) == 0);

  if (m_topChunkHeader == nullptr) UNLIKELY
  {
    AllocateNewChunk(AllocSize + Alignment);
  }

  uint8* result = MEngine::Core::Align(m_topChunkHeader->Top(), Alignment);
  uint8* nextTop = result + AllocSize;

  if (nextTop <= m_topChunkHeader->End())
  {
    m_topChunkHeader->UsedSize += AllocSize;
  }
  // Remaning size is not enough.Allocate a new chunk
  else
  {
    AllocateNewChunk(AllocSize + Alignment);
    result = MEngine::Core::Align(m_topChunkHeader->Top(), Alignment);
    m_topChunkHeader->UsedSize += AllocSize;
  }

  return result;
}

bool MemChunkStack::IsEmpty() const
{
  return m_topChunkHeader == nullptr;
}

void MemChunkStack::AllocateNewChunk(IN SIZE_T MinSize)
{
  constexpr SIZE_T firstPageHeaderReserve = 32;
  constexpr SIZE_T firstPageSize = 1024 - firstPageHeaderReserve;
  constexpr SIZE_T perPageSize = 64 * 1024;

  SIZE_T candidateTotalSize = MinSize + sizeof(ChunkHeader);
  SIZE_T allocSize = 0;
  if ((m_topChunkHeader != nullptr) || (candidateTotalSize > firstPageSize))
  {
    allocSize = MEngine::Core::AlignAny<SIZE_T>(candidateTotalSize, perPageSize);
  }
  else
  {
    allocSize = firstPageSize;
  }

  // TODO Stop using malloc.Use platform-base memory allocation function immediately
  // NOTE:Platform-base memory allocation strategy is not existing right now
  ChunkHeader* newChunk = reinterpret_cast<ChunkHeader*>(::malloc(allocSize));
  me_assert(newChunk != nullptr);

  newChunk->Next = m_topChunkHeader;
  newChunk->Size = allocSize - sizeof(ChunkHeader);
  newChunk->UsedSize = 0;

  m_topChunkHeader = newChunk;
}

void MemChunkStack::FreeChunks(IN ChunkHeader* NewTopChunkHeader)
{
  while (m_topChunkHeader != NewTopChunkHeader)
  {
    ChunkHeader* chunkToRemove = m_topChunkHeader;
    m_topChunkHeader           = m_topChunkHeader->Next;

    // TODO Stop using free.Use platform-base memory allocation strategy immediately
    // NOTE:Platform-base memory allocation strategy is not existing right now
    ::free(chunkToRemove);
  }
}

} // namespace MEngine::Core

} // namespace MEngine