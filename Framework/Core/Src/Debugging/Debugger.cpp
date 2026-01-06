#include "Debugging/Debugger.h"

#include "Math/MEngineMathUtility.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformStringUtility.h"
#include "Misc/ConceptsStoragePlace.h"

#include <source_location>
#include <string>
#include <cstdarg>

namespace
{
  constexpr int32 ASSERT_BUFFER_SIZE = 4096;
  constexpr const TCHAR* ASSERT_MSG_HEADER = MTEXT("!!!Assertion Failed:");

  FORCENOINLINE void LogAssertMessageStatic(
    IN const TCHAR*     ErrorHeader,
    IN const ANSICHAR*  Expression,
    IN const ANSICHAR*  FileName,
    IN const ANSICHAR*  FuncName,
    IN const uint32     Line,
    OUT TCHAR* FormattedLog,
    IN const SIZE_T FormattedLogSize);

  /**
   * AssertBufferWriter
   */
  template<SIZE_T BufferSize>
  struct MAssertBufferWriter
  {
    MAssertBufferWriter(const MAssertBufferWriter& Other) = delete;
    MAssertBufferWriter& operator=(const MAssertBufferWriter& Other) = delete;
    MAssertBufferWriter(MAssertBufferWriter&& OTher) noexcept = delete;
    MAssertBufferWriter& operator=(MAssertBufferWriter&& Other) noexcept = delete;

    explicit MAssertBufferWriter()
      : m_index(0)
      , m_assertBuffer()
    {
      m_assertBuffer[0] = static_cast<TCHAR>(0); 
    }

    ~MAssertBufferWriter()
    {
      FinishWrite();
    }

    void FinishWrite()
    {
      m_assertBuffer[m_index] = static_cast<TCHAR>(0);
    }

    const TCHAR* GetBuffer() const
    {
      return m_assertBuffer;
    }

    template<CHAR_TYPE_CONCEPT CharType>
    void Append(IN const CharType* Str)
    {
      const SIZE_T strLength = MPlatformStringUtility::Strlen(Str);
      const SIZE_T requiredLength = MPlatformStringUtility::ConvertedLength<TCHAR>(Str, strLength);
      if (requiredLength + m_index < BufferSize)
      {
        MPlatformStringUtility::ConvertToDest(m_assertBuffer + m_index, requiredLength, Str, strLength);
        m_index += requiredLength;
      }
    }

    void AppendFormatted(IN const TCHAR* Format, ...)
    {
      va_list args;
      va_start(args, Format);
      AppendVaList(Format, args);
      va_end(args);
    }

    void AppendVaList(IN const TCHAR* Format, IN va_list Args)
    {
      const int32 writtenBufferCnt = MPlatformStringUtility::PrintBufferV(m_assertBuffer + m_index, BufferSize - m_index, Format, Args);
      m_index = MMath::Clamp(m_index, writtenBufferCnt+ m_index, BufferSize - 1);
    }

    void EndLine()
    {
      if (m_index >= BufferSize)
      {
        return;
      }

      Append(MTEXT("\n"));
    }

    private:
      SIZE_T m_index;
      TCHAR m_assertBuffer[BufferSize];
  };
}

namespace MEngine
{
  namespace Core
  {
    MDebugger* GDebugger = nullptr;

    MDebugger* MDebugger::CreateDefaultDebugger()
    {
      
      if (GDebugger != nullptr)
      {
        // TODO Weird design
        ReleaseCurrentDebugger();
      }
      GDebugger = new MDebugger();

      return GDebugger;
    }

    void MDebugger::ReleaseCurrentDebugger()
    {
      delete GDebugger;
      GDebugger = nullptr;
    }

    void MDebugger::PreAssert(IN const ANSICHAR* Expression, 
                              IN const ANSICHAR* FileName  ,
                              IN const ANSICHAR* FuncName  ,
                              IN const uint32 Line) const
    { 
      // Empty implementation, override in derived class if needed
      (void)Expression;
      (void)FileName;
      (void)FuncName;
      (void)Line;
    }

    void MDebugger::PostAssert(IN const TCHAR* FormattedStr) const
    {
     ::wprintf(FormattedStr);
      // Empty implementation, override in derived class if needed
    }
 
    bool MDebugger::AssertImpl( IN const ANSICHAR* Expression, 
                                IN const ANSICHAR* FileName  ,
                                IN const ANSICHAR* FuncName  ,
                                IN const uint32 Line)
    {
      if (GDebugger != nullptr) UNLIKELY
      {
        GDebugger->PreAssert(Expression, FileName, FuncName, Line);
      }

      TCHAR formattedLog[ASSERT_BUFFER_SIZE];
      LogAssertMessage(Expression, FileName, FuncName, Line, formattedLog, ASSERT_BUFFER_SIZE);

      if (GDebugger != nullptr) UNLIKELY
      {
        GDebugger->PostAssert(formattedLog);
      }

      return true;
    }

    bool MDebugger::AssertImplSrcLoc(IN const ANSICHAR* Expression,
                                     IN const std::source_location& SourceLocation)
    {
      return AssertImpl(
        Expression, 
        SourceLocation.file_name(),
        SourceLocation.function_name(),
        static_cast<uint32>(SourceLocation.line())
      );
    }                                

    void MDebugger::LogAssertMessage( IN const ANSICHAR* Expression, 
                                              IN const ANSICHAR* FileName  ,
                                              IN const ANSICHAR* FuncName  ,
                                              IN const uint32 Line,
                                              OUT TCHAR* OutFormattedLog,
                                              IN const SIZE_T FormattedCount)
    {
      LogAssertMessageStatic(ASSERT_MSG_HEADER, Expression, FileName, FuncName, Line, OutFormattedLog, FormattedCount);
    }
  }
}

namespace
{
  FORCENOINLINE void LogAssertMessageStatic(
    IN const TCHAR*     ErrorHeader,
    IN const ANSICHAR*  Expression,
    IN const ANSICHAR*  FileName,
    IN const ANSICHAR*  FuncName,
    IN const uint32     Line,
    OUT TCHAR* FormattedLog,
    IN const SIZE_T FormattedLogCount)
  {

    MAssertBufferWriter<ASSERT_BUFFER_SIZE> writer;
    writer.Append(ErrorHeader);
    writer.Append(Expression);
    writer.Append(FileName);
    writer.Append(FuncName);
    writer.AppendFormatted(MTEXT("[Line:%d]"),Line);
    writer.EndLine();
    writer.FinishWrite();

    MPlatformLowLevelAccessPort::PlatformPrintToLocalDevice(writer.GetBuffer());

    const SIZE_T formattedCount = MMath::Min(static_cast<SIZE_T>(ASSERT_BUFFER_SIZE), FormattedLogCount);
    MPlatformStringUtility::Strcpy(FormattedLog, writer.GetBuffer(), formattedCount);
  }
}