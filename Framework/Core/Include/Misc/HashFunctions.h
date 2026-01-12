#pragma once

#ifndef _ME_CORE_HASHFUNCTIONS_
#define _ME_CORE_HASHFUNCTIONS_

#include "CoreDefines.h"

namespace MEngine
{

namespace Core
{

template<typename UnsignedIntegerType>
struct MFNV1aTypeTraits;

template<>
struct MFNV1aTypeTraits<uint32>
{
  // FNV prime
  // hex: 0x01000193
  // dec: 16777619
  static constexpr uint32 FNV_Prime = 16777619;

  // FNV offset basis. 
  // hex: 0x811c9dc5
  // dec: 2166136261
  static constexpr uint32 FNV_Offset_Basis = 2166136261;
};

template<>
struct MFNV1aTypeTraits<uint64>
{
  // FNV prime
  // hex: 0x00000100000001b3
  // dec: 1099511628211
  static constexpr uint64 FNV_Prime = 1099511628211ull;

  // FNV offset basis. 
  // hex: 0xcbf29ce484222325
  // dec: 14695981039346656037
  static constexpr uint64 FNV_Offset_Basis = 14695981039346656037ull;
};

template<typename HashType>
FORCEINLINE HashType FNV1a(IN const void* Src, IN SIZE_T Size)
{
  HashType result = MFNV1aTypeTraits<HashType>::FNV_Offset_Basis;

  const uint8* scrTemp = reinterpret_cast<const uint8*>(Src);
  for (SIZE_T i = 0; i < Size; ++i)
  {
    result ^= srcTemp[i];
    result *= MFNV1aTypeTraits<HashType>::FNV_Prime;
  }

  return result;
}

FORCEINLINE uint32 FNV1a32(IN const void* Src, IN SIZE_T Size)
{
  return FNV1a<uint32>(Src, Size);
}

FORCEINLINE uint64 FNV1a64(IN const void* Src, IN SIZE_T Size)
{
  return FNV1a<uint64>(Src, Size);
}

}

}



#endif // _ME_CORE_HASHFUNCTIONS_