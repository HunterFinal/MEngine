#pragma once

#ifndef _ME_CORE_GENERIC_PLATFORM_STRING_UTILITY_
#define _ME_CORE_GENERIC_PLATFORM_STRING_UTILITY_

#include "CoreDefines.h"
#include "Macro/CPPVerMacro.h"
#include "Misc/ConceptsStoragePlace.h"
#include "Templates/IsCharEncodingCompatibleTypeTraits.h"
#include "Templates/IsCharFixedWidthTypeTraits.h"

#ifndef MENGINE_CORRUPTED_CHAR_CONVERSION_REPLACEMENT
  #define MENGINE_CORRUPTED_CHAR_CONVERSION_REPLACEMENT '?'
#endif

static_assert(sizeof(MENGINE_CORRUPTED_CHAR_CONVERSION_REPLACEMENT) <= sizeof(ANSICHAR),"The corrupted conversion char to replace is expected to fit in a single ANSICHAR.");

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
        CORE_API static int32 Strcmp(const ANSICHAR* Str1, const ANSICHAR* Str2);
        CORE_API static int32 Strcmp(const WIDECHAR* Str1, const WIDECHAR* Str2);

        template<CHAR_TYPE_CONCEPT DestEncoding, CHAR_TYPE_CONCEPT SrcEncoding>
        static FORCEINLINE constexpr bool CanConvertChar(IN SrcEncoding Ch)
        {
          using namespace MEngine::TypeTraits;
          static_assert(IsCharFixedWidth_V<SrcEncoding>, "Source encoding is not fixed-width");

          // Convert a smaller one to a wider one should always be possible 
          if constexpr (IsCharFixedWidth_V<SrcEncoding> && sizeof(SrcEncoding) <= sizeof(DestEncoding))
          {
            return true;
          }
          // Converting all character to a variable-width(UTF-8) encoding should always be possible
          else if constexpr (!IsCharFixedWidth_V<DestEncoding>)
          {
            return true;
          }
          else if constexpr (std::is_same_v<std::remove_cvref_t<DestEncoding>, ANSICHAR>)
          {
            return static_cast<uint32>(Ch) < 0x7f;
          }
          else
          {
            // This only taken from UTF32CHAR(4 byte)-> 2 byte encoding(UCS2CHAR or WIDECHAR on Windows)
            static_assert(sizeof(DestEncoding) == 2 && sizeof(SrcEncoding) == 4, "Unknown conversion");

            return static_cast<uint32>(Ch) < 0xffff;
          }
        }

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
            for (SIZE_T i = 0; i < ConvertSize; ++i)
            {
              SourceEncoding SrcChar = SrcAddress[i];
              DestAddress[i] = static_cast<DestinationEncoding>(SrcChar);
            }

            // Return nullptr if source string is not fully converted
            return (DestSize < SrcSize) ? nullptr : (DestAddress + SrcSize);
          }
          // Lossy conversion from fixed-width source encoding to a fixed-width smaller encoding(May cause character loss)
          else if constexpr (IsCharFixedWidth_V<SourceEncoding> && IsCharFixedWidth_V<DestinationEncoding>)
          {
            const SIZE_T convertSize = DestSize <= SrcSize ? DestSize : SrcSize;
            bool bHasCorruptedChar = false;
            for (SIZE_T i = 0; i < convertSize; ++i)
            {
              SourceEncoding SrcChar = SrcAddress[i];
              DestAddress[i] = static_cast<DestinationEncoding>(SrcChar);

              bHasCorruptedChar |= !CanConvertChar<DestinationEncoding>(SrcChar);
            }

            if (bHasCorruptedChar)
            {
              for (SIZE_T i = 0; i < convertSize; ++i)
              {
                if (!CanConvertChar<DestinationEncoding>(SrcAddress[i]))
                {
                  DestAddress[i] = MENGINE_CORRUPTED_CHAR_CONVERSION_REPLACEMENT;
                }
              }
            }

            return DestSize < SrcSize ? nullptr : DestAddress + convertSize;
          }
          else
          {
            // FIXME 
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
            (MEngine::TypeTraits::IsCharFixedWidth_V<SourceEncoding> && (sizeof(SourceEncoding) <= sizeof(DestinationEncoding))) ||
            (MEngine::TypeTraits::IsCharFixedWidth_V<SourceEncoding> && MEngine::TypeTraits::IsCharFixedWidth_V<DestinationEncoding>)
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