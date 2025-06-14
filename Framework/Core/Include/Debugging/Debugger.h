#pragma once

#ifndef _ME_CORE_DEBUGGER_
#define _ME_CORE_DEBUGGER_

#include "Misc/CoreDefines.h"

#include <cassert>
#include <type_traits>

namespace std
{
  struct source_location;
}

namespace MEngine
{
  namespace Core
  {
    extern CORE_API class MDebugger* GDebugger;

    class MDebugger
    {      
      public:
        template<typename DebuggerType, typename... ConstructArgTypes>
        static void ReplaceGDebugger(ConstructArgTypes... Args);

        CORE_API static MDebugger* CreateDefaultDebugger();
        CORE_API static void ReleaseCurrentDebugger();

      protected:
        CORE_API virtual void PreAssert(IN const ANSICHAR* Expression, 
                                        IN const ANSICHAR* FileName  ,
                                        IN const ANSICHAR* FuncName  ,
                                        IN const uint32 Line) const;
        
        CORE_API virtual void PostAssert(IN const TCHAR* FormattedStr) const;
        
      protected:
        CORE_API explicit MDebugger() = default;
        CORE_API virtual ~MDebugger() = default;

      public:
        CORE_API static bool AssertImpl(IN const ANSICHAR* Expression, 
                                        IN const ANSICHAR* FileName  ,
                                        IN const ANSICHAR* FuncName  ,
                                        IN const uint32 Line);

        CORE_API static bool AssertImplSrcLoc(IN const ANSICHAR* Expression,
                                              IN const std::source_location& SourceLocation);   

        CORE_API static void LogAssertMessage(IN const ANSICHAR* Expression, 
                                              IN const ANSICHAR* FileName  ,
                                              IN const ANSICHAR* FuncName  ,
                                              IN const uint32 Line,
                                              OUT TCHAR* OutFormattedLog,
                                              IN const SIZE_T FormattedLogCount);

      public:
        MDebugger(const MDebugger& Other) = delete;
        MDebugger& operator=(const MDebugger& Other) = delete;
        MDebugger(MDebugger&& Other) noexcept = default;
        MDebugger& operator=(MDebugger&& Other) noexcept = default;

    };

    template<typename DebuggerType, typename... ConstructArgTypes>
    void MDebugger::ReplaceGDebugger(ConstructArgTypes... Args)
    {
      static_assert(std::is_base_of<MDebugger, DebuggerType>::value, "Can not replace debugger with non-derived class");
      if (GDebugger != nullptr)
      {
        ReleaseCurrentDebugger();
      }

      GDebugger = new DebuggerType(Args...);
    }
  }
}


#endif // _ME_CORE_DEBUGGER_