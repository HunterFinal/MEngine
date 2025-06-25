#include "Generic/GenericPlatformStringUtility.h"

#include "Math/MEngineMathUtility.h"

#include <cstring>

namespace MEngine
{
  namespace Core
  {
    SIZE_T MGenericPlatformStringUtility::PrivateInner::CalcConvertedLength(const WIDECHAR* DestAddress, const UTF8CHAR* SrcAddress, const SIZE_T SrcLength)
    {
      // TODO
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
  }
}