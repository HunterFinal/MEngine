#include "Utils/FileHelper.h"

#include "Macro/AssertionMacros.h"
#include "Serialization/SerializationConcepts.h"
#include "Serialization/FileSerializer.h"
#include "HAL/PlatformFileSystem.h"
#include "HAL/PlatformStringUtility.h"

#include <vector>
#include <unordered_map>


namespace
{
  enum class EBufferTextEncoding
  {
    UTF8,     // UTF-8 BOM
    UTF16_LE,
    UTF16_BE,
    UTF32_LE,
    UTF32_BE,
    ANSI
  };

  struct BOMResult
  {
    EBufferTextEncoding Encoding;
    SIZE_T BOMSize;
  };

  BOMResult DetectBOM(IN const uint8* Src, IN int64 Size);

  template<MEngine::Core::ReadFileSerializer TSerializer>
  bool TempReadFileToString(OUT std::wstring& OutString, OUT TSerializer& Serializer);

  void ConvertBufferToWString(OUT std::wstring& OutResult, IN const uint8* SrcBuffer, IN int64 Size);
} // nameless namespace

namespace Private
{
  void ANSIToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size);
  void UTF8ToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size);
  void UTF16LEToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size);
  void UTF16BEToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size);
}

namespace MEngine
{

namespace Core
{

bool MFileHelper::ReadFileToString(IN const TCHAR* Filename, OUT std::wstring& OutString)
{
  bool bSuccess = false;

  // // TODO We currently read file in single-thread enviornment
  {
    std::unique_ptr<MFileReadSerializer> reader{FileSystem::CreateFileReader(Filename)};
    if (reader != nullptr)
    {
      bSuccess = TempReadFileToString(OutString, *reader);
    } 
  }

  return bSuccess;
}

} // namespace MEngine::Core

} // namespace MEngine

namespace
{
  BOMResult DetectBOM(IN const uint8* Src, IN int64 Size)
  {
    me_assert(Src != nullptr);

    // UTF-8 BOM (EF BB BF)
    if (Size >= 3)
    {
      if (Src[0] == 0xef && Src[1] == 0xbb && Src[2] == 0xbf)
      {
        return { EBufferTextEncoding::UTF8, 3 };
      }
    }

    // UTF-16
    if (Size >= 2)
    {
      // UTF-16 LE (FF FE)
      if (Src[0] == 0xff && Src[1] == 0xfe)
      {
        return { EBufferTextEncoding::UTF16_LE, 2 };
      }
      // UTF-16 BE (FE FF)
      else if (Src[0] == 0xfe && Src[1] == 0xff)
      {
        return { EBufferTextEncoding::UTF16_BE, 2 };
      }
    }

    // Without BOM
    return { EBufferTextEncoding::ANSI, 0 }; 
    
  }

  template<MEngine::Core::ReadFileSerializer TSerializer>
  bool TempReadFileToString(OUT std::wstring& OutString, OUT TSerializer& Serializer)
  {
    const int64 size = Serializer.Size();
    if (size <= 0)
    {
      OutString.clear();
      return true;
    }

    uint8* destData = reinterpret_cast<uint8*>(::malloc(size));
    if (destData == nullptr)
    {
      OutString.clear();
      return false;
    }

    Serializer.Serialize(destData, size);
    bool bSuccess = !Serializer.IsError();

    ConvertBufferToWString(OutString, destData, size);

    ::free(destData);

    return bSuccess;
  }

  void ConvertBufferToWString(OUT std::wstring& OutResult, IN const uint8* SrcBuffer, IN int64 Size)
  {
    me_assert(SrcBuffer != nullptr);

    BOMResult result = DetectBOM(SrcBuffer, Size);

    SrcBuffer += result.BOMSize;
    Size -= result.BOMSize;

    typedef void (*ConvertFuncPtr)(std::wstring&, const uint8*, int64);
    static std::unordered_map<EBufferTextEncoding, ConvertFuncPtr> s_converter =
    {
      { EBufferTextEncoding::ANSI, Private::ANSIToWString},
      { EBufferTextEncoding::UTF8, Private::UTF8ToWString},
      { EBufferTextEncoding::UTF16_LE, Private::UTF16LEToWString},
      { EBufferTextEncoding::UTF16_BE, Private::UTF16BEToWString}
    };

    if (Size > 0)
    {
      // Convert to wstring(Encoding base)
      s_converter[result.Encoding](OutResult, SrcBuffer, Size);

      // There is only '\0' so we make it actually empty
      if (OutResult.size() == 1)
      {
        OutResult.clear();
      }
    }
  }
} // nameless namespace


namespace Private
{
  
  // TODO wstring may not contains 16-bit character in some platforms
  // FIXME Remove wstring usage immediately
  void ANSIToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size)
  {
    OutResult.clear();
    SIZE_T length = MPlatformStringUtility::ConvertedLength<TCHAR>(reinterpret_cast<const ANSICHAR*>(Src), static_cast<SIZE_T>(Size));

    // Additional 1 for '\0'
    OutResult.resize(length + 1);
    MPlatformStringUtility::ConvertToDest(OutResult.data(), length, reinterpret_cast<const ANSICHAR*>(Src), Size);
    OutResult.push_back(MTEXT('\0'));
  }

  void UTF8ToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size)
  {
    // Same as ANSI
    ANSIToWString(OutResult, Src, Size);
  }

  void UTF16LEToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size)
  {
    OutResult.clear();

    // Make sure Size is an even number
    Size &= ~1;
    // Additional 1 for '\0'
    OutResult.resize((Size / 2) + 1);

    for (int64 i = 0; i < (Size / 2); ++i)
    {
      TCHAR ch{0};
      UTF16CHAR convertedCh = static_cast<UTF16CHAR>(static_cast<uint16>(Src[i * 2]) + static_cast<uint16>(Src[i * 2 + 1]<< 8));
      MPlatformStringUtility::ConvertToDest(&ch, 1, &convertedCh, 1);
      OutResult.push_back(ch);
    }
  }

  void UTF16BEToWString(OUT std::wstring& OutResult, IN const uint8* Src, IN int64 Size)
  {
    OutResult.clear();

    // Make sure Size is an even number
    Size &= ~1;
    // Additional 1 for '\0'
    OutResult.resize((Size / 2) + 1);

    for (int64 i = 0; i < (Size / 2); ++i)
    {
      TCHAR ch{0};
      UTF16CHAR convertedCh = static_cast<UTF16CHAR>(static_cast<uint16>(Src[i * 2 + 1]) + static_cast<uint16>(Src[i * 2]<< 8));
      MPlatformStringUtility::ConvertToDest(&ch, 1, &convertedCh, 1);
      OutResult.push_back(ch);
    }
  }
} // namespace Private