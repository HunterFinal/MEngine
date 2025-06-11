#include "Debugging/Debugger.h"

#include "Math/MEngineMathUtility.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "HAL/PlatformStringUtility.h"
#include "Misc/ConceptsStoragePlace.h"

#include <string>

namespace
{
  constexpr int32 ASSERT_BUFFER_SIZE = 4096;
  constexpr const TCHAR* ASSERT_MSG_HEADER = MTEXT("!!!Assertion Failed:");

  FORCENOINLINE void LogAssertMessageStatic(
    IN const TCHAR*     ErrorHeader,
    IN const ANSICHAR*  Expression,
    IN const ANSICHAR*  FileName,
    IN const ANSICHAR*  FuncName,
    IN const uint32     Line);

  /**
   * AssertBufferWriter
   */
  template<SIZE_T Size>
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
      if (requiredLength + m_index < Size)
      {
        MPlatformStringUtility::ConvertToDest(m_assertBuffer + m_index, requiredLength, Str, strLength);
        m_index += requiredLength;
      }
    }

    private:
      SIZE_T m_index;
      TCHAR m_assertBuffer[Size];
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
        GDebugger = new MDebugger();
      }

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
    }

    void MDebugger::PostAssert( IN const ANSICHAR* Expression, 
                                IN const ANSICHAR* FileName  ,
                                IN const ANSICHAR* FuncName  ,
                                IN const uint32 Line) const
    {
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

      LogAssertMessage(Expression, FileName, FuncName, Line);

      if (GDebugger != nullptr) UNLIKELY
      {
        GDebugger->PostAssert(Expression, FileName, FuncName, Line);
      }

      return true;
    }

    void MDebugger::LogAssertMessage( IN const ANSICHAR* Expression, 
                                      IN const ANSICHAR* FileName  ,
                                      IN const ANSICHAR* FuncName  ,
                                      IN const uint32 Line)
    {
      // TODO
      LogAssertMessageStatic(ASSERT_MSG_HEADER, Expression, FileName, FuncName, Line);
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
    IN const uint32     Line)
  {

    MAssertBufferWriter<4096> writer;
    writer.Append(ErrorHeader);
    writer.Append(Expression);
    writer.Append(FileName);
    writer.Append(FuncName);
    writer.FinishWrite();

    MPlatformLowLevelAccessPort::OutputDebugString(writer.GetBuffer());
  }
}