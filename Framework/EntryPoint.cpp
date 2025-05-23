// MEngine entry point

#include <iostream>
#include "OTGTAPI.h"
#include "ApplicationAPI.h"

// TODO
#include <spdlog/fmt/bundled/format.h>
#include <cstring>

// #define CONSOLE_MAIN
#define WINDOWGUI_MAIN

class TestCase1 final : public OTGT::ITestCaseInterface
{
  public:
    TestCase1() = default;
  private: 
    void StartupTest_Implementation() const override
    {

    }

    void RunTest_Implementation() const override
    {
      // Abs Test(Integer)
      assert(MMath::Abs(-2) == 2);
      assert(MMath::Abs(2) == 2);
      // Abs Test(Floating-type)
      assert(MMath::IsNearlyEquals(MMath::Abs(-2.2), 2.2));
      assert(MMath::IsNearlyEquals(MMath::Abs(2.2), 2.2));
      assert(MMath::IsNearlyEquals(MMath::Abs(-1.11f), 1.11f));
      assert(MMath::IsNearlyEquals(MMath::Abs(1.11f), 1.11f));
      // IsNearlyZero Test
      assert(MMath::IsNearlyZero(0.000000001f));
      assert(MMath::IsNearlyZero(0.000000001));
      assert(MMath::IsNearlyZero(0.000000001l));
      assert(MMath::IsNearlyZero(0.0f));
      assert(MMath::IsNearlyZero(0.0));
      assert(MMath::IsNearlyZero(0.0l));

      // Max Text(Integer)
      assert(MMath::Max(22, 33) == 33);
      assert(MMath::Max(0, 0) == 0);
      assert(MMath::Max(-22, -33) == -22);

      // 
    

      
      // Sign Test(Integer)
      assert(MMath::Sign(-2) == -1);
      assert(MMath::Sign(2) == 1);
      assert(MMath::Sign(0) == 0);
      
    }
};


#if defined(CONSOLE_MAIN)
int main(int argc, char** argv)
#elif defined(WINDOWGUI_MAIN)
#include <windows.h>
#include <tchar.h>
int APIENTRY _tWinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPTSTR lpCmdLinem, IN int32 nShowCmd)
#endif
{
  
  MEngine::Core::IOutputInterface* logger = new MEngine::Core::ConsoleLogger();
  logger->Startup();
  {
    int a = 5;
    double b = 3.14;
    // TODO
    std::string str = fmt::format("ABCDE{},{}", a, b);
    std::cout << str << std::endl;
    logger->Serialize(str.c_str());
  }

  {
    IApplicationInterface* app = GenerateAPP();
    if (app != nullptr)
    {
      app->Startup();
      app->Terminate();
    }
    delete app;
  }

  {
    OTGT::ITestCaseInterface* pTest = new TestCase1();
    pTest->RunTest_Interface();
    delete pTest;
  }

  int a;
  std::cin >> a;
  logger->Terminate();
  delete logger;
  return 0;
}

