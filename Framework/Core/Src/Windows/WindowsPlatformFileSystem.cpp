#include "Windows/WindowsPlatformFileSystem.h"
#include "Windows/WindowsHeaderSet.h"
#include "Macro/AssertionMacros.h"
#include "Macro/BitOperationMacros.h"
// TODO
#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformMath.h"

#include "Serialization/FileSerializer.h"

#include <memory>
// TODO
#include <iostream>

// TODO
#ifndef PLATFORM_FILE_READER_BUFFER_SIZE
  #define PLATFORM_FILE_READER_BUFFER_SIZE 1024
#endif

namespace
{
  void UpdateOverlappedPos(OUT OVERLAPPED& OutOverlappedIO, int64 UpdatedPos);
}

class MWindowsFileHandler
{
  TYPEDEF(std::wstring, MString);

  public:
    enum EFileAccessMode : uint8
    {
      AllowRead = BIT_FLAG(0),
      AllowWrite = BIT_FLAG(1),

      AllowReadWrite = AllowRead | AllowWrite,
    };

    enum EFileShareMode : uint8
    {
      None = BIT_FLAG(2),
      ShareRead = BIT_FLAG(3),
      ShareWrite = BIT_FLAG(4),
      ShareDelete = BIT_FLAG(5),
    };

    enum EFileCreationDisposition : uint8
    {
      OverwriteEvenExist = BIT_FLAG(6),
    };

    MWindowsFileHandler(IN const TCHAR* Filename, IN uint8 FileFlags)
      : m_filename{Filename}
      , m_fileHandle{INVALID_HANDLE_VALUE}
      , m_pos{0}
      , m_size{-1}
      , m_flags{FileFlags}
    {
      me_assert(Filename != nullptr);

      ::memset(&m_overlappedIO, 0, sizeof(OVERLAPPED));
    }

    ~MWindowsFileHandler()
    {
      Close();
    }

  public:
    bool Open()
    {
      // Skip if file is already opened
      if (IsOpen())
      {
        return false;
      }

      // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/fileapi/nf-fileapi-createfilew
      const DWORD fileAccess = (IsLoading() ? GENERIC_READ : 0) | (IsSaving() ? GENERIC_WRITE : 0);
      const bool bIsReadonly = !(!!(fileAccess ^ GENERIC_READ));

      // Readonly file can share write and delete too
      const DWORD fileSharedMode = ((m_flags & EFileShareMode::ShareRead) == EFileShareMode::ShareRead ? FILE_SHARE_READ : 0) | 
                                   ((bIsReadonly && (m_flags & EFileShareMode::ShareWrite) == EFileShareMode::ShareWrite) ? FILE_SHARE_WRITE : 0) |
                                   ((bIsReadonly && (m_flags & EFileShareMode::ShareDelete) == EFileShareMode::ShareDelete) ? FILE_SHARE_DELETE : 0);
      
      const DWORD fileCreationDisposition = bIsReadonly ? OPEN_EXISTING : 
                                            ((m_flags & EFileCreationDisposition::OverwriteEvenExist) ? CREATE_ALWAYS : OPEN_ALWAYS);

      // NOTE:Third argument [lpSecurityAttributes] need research
      // NOTE:Sixth argument FILE_FLAG_OVERLAPPED is added when we need Async IO
      m_fileHandle = ::CreateFile(
                                    m_filename.c_str(), 
                                    fileAccess, 
                                    fileSharedMode,
                                    NULL,
                                    fileCreationDisposition,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL
                                  );

      // Read file failed
      if (m_fileHandle == INVALID_HANDLE_VALUE)
      {
        return false;
      }

      // Update file size when load success
      UpdateFileSize();

      return true;
    }

    bool Close()
    {
      if (m_fileHandle != INVALID_HANDLE_VALUE)
      {
        (void)::CloseHandle(m_fileHandle);
        m_fileHandle = INVALID_HANDLE_VALUE;
        m_pos = 0;
        m_size = -1;
      }

      return true;
    }

    bool IsValid() const
    {
      return IsOpen() && m_size != -1;
    }

    bool IsOpen() const
    {
      return m_fileHandle != INVALID_HANDLE_VALUE;
    }

    bool IsLoading() const
    {
      return (m_flags & EFileAccessMode::AllowRead) == EFileAccessMode::AllowRead;
    }

    bool IsSaving() const
    {
      return (m_flags & EFileAccessMode::AllowWrite) == EFileAccessMode::AllowWrite;
    } 

    int64 Tell() const
    {
      me_assert(IsValid());
      return m_pos;
    }

    int64 Size() const
    {
      me_assert(IsValid());
      return m_size;
    }

    void Seek(int64 NewPos)
    {
      me_assert(IsValid());
      me_assert(NewPos >= 0);

      m_pos = NewPos;
      ::UpdateOverlappedPos(m_overlappedIO, m_pos);
    }

    bool Read(uint8* Destination, int64 BytesToRead)
    {
      me_assert(IsValid());

      if (!IsValid())
      {
        return false;
      }

      // Ignore write-only file
      if (!IsLoading())
      {
        return false;
      }

      
      do
      {
        BOOL bSuccess{};
        DWORD bytesProcessed{0};

        // NOTE:There is some restriction IN Wine(Run windows executable on Linux/macOS)
        const DWORD actualBytesToRead = static_cast<DWORD>(MPlatformMath::Min(BytesToRead, int64{UINT32_MAX}));
        // NOTE: There is also a ReadFileEx function. Need research
        // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/fileapi/nf-fileapi-readfile
        bSuccess = ::ReadFile(
                                m_fileHandle,
                                static_cast<void*>(Destination),
                                actualBytesToRead,
                                &bytesProcessed,
                                &m_overlappedIO
                             );

        if (!bSuccess)
        {
          uint32 errorCode = MPlatformLowLevelAccessPort::GetLastError();
          if (errorCode != ERROR_IO_PENDING)
          {
            return false;
          }

          // Wait for the async I/O read to complete
          bytesProcessed = 0;
          constexpr BOOL bWait = true;
          if (!::GetOverlappedResult(m_fileHandle, &m_overlappedIO, &bytesProcessed, bWait))
          {
            return false;
          }
        }

        BytesToRead -= static_cast<int64>(bytesProcessed);
        Destination += static_cast<int64>(bytesProcessed);

        // Update where we are in the file
        m_pos += static_cast<int64>(bytesProcessed);
        ::UpdateOverlappedPos(m_overlappedIO, m_pos);

      } while (BytesToRead > 0);
      
      return true;
    }

    bool Write(const uint8* Source, int64 BytesToRead)
    {
      me_assert(IsValid());

      if (!IsValid())
      {
        return false;
      }

      // Ignore read-only file
      if (!IsSaving())
      {
        return false;
      }

      do
      {
        BOOL bSuccess{};
        DWORD bytesProcessed{0};

        // NOTE:There is some restriction IN Wine(Run windows executable on Linux/macOS)
        const DWORD actualBytesToWrite = static_cast<DWORD>(MPlatformMath::Min(BytesToRead, int64{UINT32_MAX}));
        // NOTE: There is also a ReadFileEx function. Need research
        // URL:https://learn.microsoft.com/ja-jp/windows/win32/api/fileapi/nf-fileapi-readfile
        bSuccess = ::WriteFile(
                                m_fileHandle,
                                static_cast<const void*>(Source),
                                actualBytesToWrite,
                                &bytesProcessed,
                                &m_overlappedIO
                             );

        if (!bSuccess)
        {
          uint32 errorCode = MPlatformLowLevelAccessPort::GetLastError();

          if (errorCode != ERROR_IO_PENDING)
          {
            return false;
          }
          // Wait for the async I/O read to complete
          bytesProcessed = 0;
          constexpr BOOL bWait = true;
          if (!::GetOverlappedResult(m_fileHandle, &m_overlappedIO, &bytesProcessed, bWait))
          {
            return false;
          }
        }

        BytesToRead -= static_cast<int64>(bytesProcessed);
        Source += static_cast<int64>(bytesProcessed);

        // Update where we are in the file
        m_pos += static_cast<int64>(bytesProcessed);
        ::UpdateOverlappedPos(m_overlappedIO, m_pos);
        
        // Update file size during writing
        m_size = MPlatformMath::Max(m_size, m_pos);

      } while (BytesToRead > 0);

      return true;
    }

  private:
    void UpdateFileSize()
    {
      LARGE_INTEGER LI{};
      BOOL bSuccess = ::GetFileSizeEx(m_fileHandle, &LI);
      if (!bSuccess)
      {
        m_size = -1;

        // TODO
        std::cout << "Failed to get file size. Error code:" << MPlatformLowLevelAccessPort::GetLastError(); 
      }
      else
      {
        m_size = LI.QuadPart;
      }
    }

  private:
    MString m_filename;
    HANDLE m_fileHandle;
    OVERLAPPED m_overlappedIO;

    int64 m_pos;
    int64 m_size;

    const uint8 m_flags;
};  


struct MWindowsFileOperator
{
  static MWindowsFileHandler* OpenFile_Read(IN const TCHAR* Filename)
  {
    me_assert(Filename != nullptr);

    constexpr uint8 fileOpenFlags = static_cast<uint8>(MWindowsFileHandler::EFileAccessMode::AllowRead) | // Readonly
                                    static_cast<uint8>(MWindowsFileHandler::EFileShareMode::ShareRead | MWindowsFileHandler::EFileShareMode::ShareWrite); // Share read and write

    MWindowsFileHandler* fileHandle = new MWindowsFileHandler(Filename, fileOpenFlags);
    
    // Maybe we should handle error message at another place
    if (!fileHandle->Open())
    {
      // Open failed
      me_assert(fileHandle->IsValid());
      std::cout << "Error Code:" << MPlatformLowLevelAccessPort::GetLastError() << std::endl;
      return nullptr;
    }
    
    return fileHandle;
  }
};

namespace MEngine
{

namespace Core
{
  MFileReadSerializer* MWindowsPlatformFileSystem::CreateFileReader(IN const TCHAR* Filename)
  {
    MWindowsFileHandler* fileHandler = MWindowsFileOperator::OpenFile_Read(Filename);

    if (fileHandler == nullptr)
    {
      std::wcout << L"Failed to read file :" << Filename << std::endl;
      return nullptr;
    }

    constexpr SIZE_T FILE_READ_SERIALIZER_BUFFER_SIZE = PLATFORM_FILE_READER_BUFFER_SIZE;
    return new MFileReadSerializer(fileHandler, Filename, fileHandler->Size(), FILE_READ_SERIALIZER_BUFFER_SIZE);
  }

  MFileWriteSerializer* MWindowsPlatformFileSystem::CreateFileWriter(IN const TCHAR* Filename)
  {
    // FIXME Need implementation
    return nullptr;
  }

} // namespace MEngine::Core

} // namespace MEngine

namespace
{
  void UpdateOverlappedPos(OUT OVERLAPPED& OutOverlappedIO, int64 UpdatedPos)
  {
    ULARGE_INTEGER LI{};
    LI.QuadPart = UpdatedPos;

    OutOverlappedIO.Offset = LI.LowPart;
    OutOverlappedIO.OffsetHigh = LI.HighPart;
  }
}
