#pragma once

#ifndef _ME_CORE_GENERIC_PLATFORM_STRING_UTILITY_
#define _ME_CORE_GENERIC_PLATFORM_STRING_UTILITY_

#include "Misc/CoreDefines.h"

#include "Macro/CPPVerMacro.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Templates/IsCharEncodingCompatibleTypeTraits.h"
#include "Templates/IsCharFixedWidthTypeTraits.h"

namespace MEngine
{
  namespace Core
  {
    struct MGenericPlatformStringUtility
    {
      private:
        struct PrivateInner
        {
          CORE_API static SIZE_T CalcConvertedLength(IN const WIDECHAR* DestAddress, IN const UTF8CHAR* SrcAddress, IN const SIZE_T SrcLength);
          CORE_API static void* MemoryCopy(OUT void* Dest, IN const void* Src, IN const SIZE_T Size);
          CORE_API static SIZE_T Min(IN const SIZE_T A, IN const SIZE_T B);
        };

      public:
        template<CHAR_TYPE_CONCEPT SourceEncoding, CHAR_TYPE_CONCEPT DestinationEncoding>
        FORCEINLINE static DestinationEncoding* ConvertToDest(
          OUT DestinationEncoding* DestAddress,
          IN const SIZE_T DestSize,
          IN const SourceEncoding* SrcAddress,
          IN const SIZE_T SrcSize
        )
        {
          // For IsCharEncodingCompatible_V and IsCharFixedWidth_V use
          using namespace MEngine::TypeTraits;
          if ((DestAddress == nullptr) || (SrcAddress == nullptr))
          {
            return nullptr;
          }

          // Compatible encoding
          if constexpr (IsCharEncodingCompatible_V<SourceEncoding, DestinationEncoding>)
          {
            if (DestSize < SrcSize)
            {
              return nullptr;
            }

            return static_cast<DestinationEncoding*>(PrivateInner::MemoryCopy(DestAddress, SrcAddress, SrcSize * sizeof(SourceEncoding))) + SrcSize;
          }
          // Fixed-width source encoding to a wider or same encoding
          else if constexpr (IsCharFixedWidth_V<SourceEncoding> && sizeof(SourceEncoding) <= sizeof(DestinationEncoding))
          {
            const SIZE_T ConvertSize = PrivateInner::Min(DestSize, SrcSize);
            for (int i = 0; i < ConvertSize; ++i)
            {
              SourceEncoding SrcChar = SrcAddress[i];
              DestAddress[i] = static_cast<DestinationEncoding>(SrcChar);
            }

            // Return nullptr if source string is not fully converted
            return (DestSize < SrcSize) ? nullptr : (DestAddress + SrcSize);
          }
          else
          {
            return nullptr;
          }
        }

        template<CHAR_TYPE_CONCEPT DestinationEncoding, CHAR_TYPE_CONCEPT SourceEncoding>
        FORCEINLINE static SIZE_T ConvertedLength(
          IN const SourceEncoding* SrcAddress, 
          IN const SIZE_T SrcLength
        )
        {
          if constexpr (
            MEngine::TypeTraits::IsCharEncodingCompatible_V<SourceEncoding, DestinationEncoding> ||
            (MEngine::TypeTraits::IsCharFixedWidth_V<SourceEncoding> && (sizeof(SourceEncoding) <= sizeof(DestinationEncoding))) 
          )
          {
            return SrcLength;
          }
          else
          {
            return PrivateInner::CalcConvertedLength(reinterpret_cast<const DestinationEncoding*>(nullptr), SrcAddress, SrcLength);
          }
        }
    };
  }
}

#endif // _ME_CORE_GENERIC_PLATFORM_STRING_UTILITY_