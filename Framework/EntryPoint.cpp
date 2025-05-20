// MEngine entry point

#include <iostream>
#include "OTGTAPI.h"
#include "ApplicationAPI.h"

using namespace std;

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

int main(int argc, char** argv)
{
  cout << -2.5 << endl;
  cout << MMath::CeilToInt32(-2.5) << endl;
  cout << 2.5 << endl;
  cout << MMath::CeilToInt32(2.5) << endl;
  cout << MMath::Fraction(-3.5) << endl;
  cout << MMath::Fraction(3.5) << endl;

  {
    OTGT::ITestCaseInterface* pTest = new TestCase1();
    pTest->RunTest_Interface();
    delete pTest;
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
    MEngine::Core::Logger* logger = new MEngine::Core::SystemLogger();
    logger->Startup();
    logger->Terminate();
    delete logger;
  }

  return 0;
}

