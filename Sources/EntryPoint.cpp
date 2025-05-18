// MEngine entry point

#include <iostream>
#include "OTGTAPI.h"

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
      // Abs Test
      assert(MMath::Abs(-2) == 2);
      assert(MMath::Abs(2) == 2);
      // Sign Test
      assert(MMath::Sign(-2) == -1);
      assert(MMath::Sign(2) == 1);
      assert(MMath::Sign(0) == 0);
      
    }
};

int main()
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

  return 0;
}

