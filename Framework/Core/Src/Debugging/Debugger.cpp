#include "Debugging/Debugger.h"
#include <cstdio>

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
      // TODO Next is to create cross-platform low level interface
      LogAssertMessageStatic(ASSERT_MSG_HEADER, Expression, FileName, FuncName, Line);
    }

  }
}