/**
 * OTGT: On The Go Test
 */
#pragma once

#ifndef OTGT_TEST_CASE_INTERFACE
#define OTGT_TEST_CASE_INTERFACE

#include "OTGTAPI.h"

namespace OTGT
{
  class TestGenerator;

  struct OTGT_API ITestCaseInterface
  {
    // TODO
    // change to private in future
    protected:
      ITestCaseInterface() = default;
      friend class TestGenerator;
    
    public:
      virtual ~ITestCaseInterface() = default;
      ITestCaseInterface(const ITestCaseInterface&) = delete;
      ITestCaseInterface& operator=(const ITestCaseInterface&) = delete;
      ITestCaseInterface(ITestCaseInterface&&) noexcept = delete;
      ITestCaseInterface& operator=(ITestCaseInterface&&) noexcept = delete;
    
      /**
       * Start up test
       */
      void StartupTest_Interface() const;

      /**
       * Run test case
       */
      void RunTest_Interface() const;

    private:
      virtual void RunTest_Implementation() const = 0;
      virtual void StartupTest_Implementation() const = 0;
  };
}

#endif