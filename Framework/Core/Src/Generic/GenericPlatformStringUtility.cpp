#include "Generic/GenericPlatformStringUtility.h"

// TODO
#include <cstring>


namespace MEngine
{
  namespace Core
  {
    SIZE_T MGenericPlatformStringUtility::PrivateInner::CalcConvertedLength(const WIDECHAR* DestAddress, const UTF8CHAR* SrcAddress, const SIZE_T SrcLength)
    {
      return 0;
    }
  
    void* MGenericPlatformStringUtility::PrivateInner::MemoryCopy(
      IN void* Dest,
      IN const void* Src,
      IN SIZE_T Size
    )
    {
      // TODO
      return ::memcpy(Dest, Src, static_cast<size_t>(Size));
    }  
  }
}