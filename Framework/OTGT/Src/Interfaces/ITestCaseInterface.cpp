#include "Interfaces/ITestCaseInterface.h"

namespace OTGT
{
  void ITestCaseInterface::StartupTest_Interface()
  {
    StartupTest_Implementation();
  }

  void ITestCaseInterface::RunTest_Interface()
  {
    RunTest_Implementation();
  }
}