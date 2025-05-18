#include "Interfaces/ITestCaseInterface.h"

namespace OTGT
{
  void ITestCaseInterface::StartupTest_Interface() const
  {
    StartupTest_Implementation();
  }

  void ITestCaseInterface::RunTest_Interface() const
  {
    RunTest_Implementation();
  }
}