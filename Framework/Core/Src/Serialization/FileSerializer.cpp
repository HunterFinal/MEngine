#include "Serialization/FileSerializer.h"
#include "HAL/PlatformStringUtility.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformMath.h"

// TODO
#include <iostream>

#ifdef ERROR_BUFFER_SIZE
#pragma push_macro("ERROR_BUFFER_SIZE")
#define ERROR_BUFFER_SIZE_PUSH_MACRO

#undef ERROR_BUFFER_SIZE
#define ERROR_BUFFER_SIZE 1024

#else 
#define ERROR_BUFFER_SIZE 1024

namespace MEngine
{

namespace Core
{

MFileReadSerializer::~MFileReadSerializer()
{
  (void)Close();
}

void MFileReadSerializer::Serialize(void* Data, int64 Length)
{
  if (m_pos + Length > m_size)
  {
    this->SetError("Read length overflow");
    return;
  }

  if (Length < 0)
  {
    this->SetError("Length of Serialize is below 0");
    return;
  }

  // Read data from file(or cache data to buffer)
  do
  {
    // Read length is greater than buffer so we directly read from file
    if (static_cast<SIZE_T>(Length) >= m_bufferSize)
    {
      bool bSuccess = m_pImpl->Read(reinterpret_cast<uint8*>(Data), Length);
      if (!bSuccess)
      {
        constexpr SIZE_T BUFFER_SIZE = ERROR_BUFFER_SIZE;
        // Convert error code
        uint32 errorCode = MPlatformLowLevelAccessPort::GetLastError();
        TCHAR errorMsg[BUFFER_SIZE];
        (void)MPlatformLowLevelAccessPort::ConvertSystemErrorMessage(errorMsg, BUFFER_SIZE, errorCode);
        
        // FIXME Currently we get all system error message in english so we can convert it directly
        ANSICHAR errorMsgEng[BUFFER_SIZE];
        MPlatformStringUtility::ConvertToDest(errorMsgEng, BUFFER_SIZE, errorMsg, BUFFER_SIZE);
        this->SetError(errorMsgEng);
      }

      m_pos += Length;
      return;
    }

    // Try to cache file data to buffer
    if (!CacheFileBuffer(m_pos))
    {
      this->SetError("FileRead serialization failed during caching file.");
      return;
    }

    const int64 copyCount = MPlatformMath::Min(Length, static_cast<int64>(m_bufferArray.size()) + m_bufferPos - m_pos);
    // Failed if we try to read nothing(Length is invalid or EOF)
    if (copyCount <= 0)
    {
      this->SetError("FileRead beyond EOF");
      return;
    }

    // copy cached data
    // FIXME Switch to Platform memory processing
    ::memcpy(Data, m_bufferArray.data() + m_bufferPos - m_pos, copyCount);

    m_pos  += copyCount;
    Length -= copyCount;
    Data    = static_cast<void*>(reinterpret_cast<uint8*>(Data) + copyCount);

  } while (Length > 0);
}

bool MFileReadSerializer::Close()
{
  m_bIsLoading = false;
  return m_pImpl->Close();
}

bool MFileReadSerializer::IsValid() const
{
  return (m_pImpl != nullptr) && m_pImpl->IsValid();
}

bool MFileReadSerializer::IsOpen() const
{
  return m_pImpl->IsOpen();
}

bool MFileReadSerializer::IsLoading() const
{
  return m_bIsLoading;
}

std::string MFileReadSerializer::GetName() const
{
  char resultBuffer[1024]{'0'};
  (void)MPlatformStringUtility::ConvertToDest(resultBuffer, SIZE_OF_ARRAY(resultBuffer), m_filename.data(), m_filename.size());

  return std::string{resultBuffer};
}

bool MFileReadSerializer::CacheFileBuffer(IN int64 CacheStartPos)
{
  if (m_bufferArray.capacity() == 0)
  {
    m_bufferArray.reserve(m_bufferSize);
  }

  // Only cache file at current position
  if (m_pos != CacheStartPos)
  {
    return false;
  }

  int64 bufferSizeToCache = MPlatformMath::Min(static_cast<int64>(m_bufferSize), m_size - m_pos);

  // Stop caching when the m_bufferSize is 0 or we reach the end of file(EOF)
  if (bufferSizeToCache <= 0)
  {
    return false;
  }

  // Do not cache if buffer data is still left
  const bool bIsInsideBufferWindow = (m_bufferPos <= m_pos) && (m_pos < static_cast<int64>(m_bufferArray.size() + m_bufferPos));
  if (bIsInsideBufferWindow)
  {
    return true;
  }
  else
  {
    // Expand the buffer to make size is same as bufferSizeToCache
    m_bufferArray.resize(bufferSizeToCache);
  }

  // Finally we cache file data into buffer
  m_bufferPos = CacheStartPos;
  const bool bSuccess = m_pImpl->Read(m_bufferArray.data(), bufferSizeToCache);

  // Read file failed but we do not SetError
  if (!bSuccess)
  {
    constexpr SIZE_T BUFFER_SIZE = ERROR_BUFFER_SIZE;
    // Convert error code
    uint32 errorCode = MPlatformLowLevelAccessPort::GetLastError();
    TCHAR errorMsg[BUFFER_SIZE];
    (void)MPlatformLowLevelAccessPort::ConvertSystemErrorMessage(errorMsg, BUFFER_SIZE, errorCode);

    // TODO
    std::wcout << L"Read file failed during caching to buffer. Error message: " << errorMsg << std::endl;
    return true;
  }

  return true;

}

} // namespace MEngine::Core

} // namespace MEngine

#undef ERROR_BUFFER_SIZE

#ifdef ERROR_BUFFER_SIZE_PUSH_MACRO
#pragma pop_macro("ERROR_BUFFER_SIZE")
#endif // ERROR_BUFFER_SIZE_PUSH_MACRO

#endif // #ifdef ERROR_BUFFER_SIZE