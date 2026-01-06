#include "Generic/GenericPlatformStringUtility.h"

#include "Macro/AssertionMacros.h"
#include "Math/MEngineMathUtility.h"

#include <cstring>

namespace
{
  template<CHAR_TYPE_CONCEPT CharType1, CHAR_TYPE_CONCEPT CharType2>
  int32 StrcmpImpl(IN const CharType1* Str1,IN const CharType2* Str2);
} // nameless namespace

namespace MEngine
{

namespace Core
{
  // FIXME Implement this function immediately
  SIZE_T MGenericPlatformStringUtility::PrivateInner::CalcConvertedLength(const WIDECHAR* DestAddress, const UTF8CHAR* SrcAddress, const SIZE_T SrcLength)
  {
    // FIXME Temporary code
    (void)DestAddress;
    (void)SrcAddress;
    (void)SrcLength;
    // TODO
    me_assert(false);

    return 0;
  }

  void* MGenericPlatformStringUtility::PrivateInner::MemoryCopy(
    OUT void* Dest,
    IN const void* Src,
    IN SIZE_T Size
  )
  {
    return ::memcpy(Dest, Src, static_cast<size_t>(Size));
  }  

  SIZE_T MGenericPlatformStringUtility::PrivateInner::Min(
    IN const SIZE_T A,
    IN const SIZE_T B
  )
  {
    return MMath::Min(A, B);
  }

  int32 MGenericPlatformStringUtility::Strcmp(const ANSICHAR* Str1, const ANSICHAR* Str2)
  {
    return StrcmpImpl(Str1, Str2);
  }

  int32 MGenericPlatformStringUtility::Strcmp(const WIDECHAR* Str1, const WIDECHAR* Str2)
  {
    return StrcmpImpl(Str1, Str2);
  }
  
} // namespace MEngine::Core

} // namespace MEngine

namespace
{
  template<CHAR_TYPE_CONCEPT CharType1, CHAR_TYPE_CONCEPT CharType2>
  int32 StrcmpImpl(IN const CharType1* Str1,IN const CharType2* Str2)
  {
    while (true)
    {
      CharType1 ch1 = *Str1++;
      CharType2 ch2 = *Str2++;

      uint32 u1 = static_cast<uint32>(ch1);
      uint32 u2 = static_cast<uint32>(ch2);

      if (u1 == u2)
      {
        // Stop continue when we reach null terminator;
        if (u1 != 0)
        {
          continue;
        }

        return 0;
      }
      else
      {
        return static_cast<int32>(u1) - static_cast<int32>(u2);
      }

    }
  };
} // nameless namespace