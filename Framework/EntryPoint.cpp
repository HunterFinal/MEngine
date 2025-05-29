// MEngine entry point

#include <iostream>
#include "OTGTAPI.h"
#include "ApplicationAPI.h"
#include "Delegates/Delegate.h"

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
    void StartupTest_Implementation() override
    {

    }

    void RunTest_Implementation() override
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

class DelegateTestClass
{
  public:
    DelegateTestClass()
      : result(0)
    { }
  public:
    void VII_Case1(int a, int b)
    {
      result = a * b;
      std::cout << result << "=" << a << "*" << b << std::endl;
    }

    int I_ConstCase1() const
    {
      return result;
    }

    float FF_Case1(float f)
    {
      return f * 3.14f;
    }

    float FF_ConstCase1(float f) const
    {
      return f * 6.28f;
    }

    void II_Case1(int a, int b)
    {
      std::cout << a + b + a << std::endl;
    }
  private:
    int result;
};

void func(int a, int b)
{
  std::cout << a / b << std::endl;
}

void func2(int a, int b)
{
  std::cout << a + b << std::endl;
}

class DelegateTestCase final : public OTGT::ITestCaseInterface
{
 public:
    DelegateTestCase()
      : m_testClassInstance(new DelegateTestClass())
    {
      Dele.BindStatic(&MMath::Sign);
      Dele2.BindClass(m_testClassInstance, &DelegateTestClass::FF_Case1);
      Dele3.BindClass(m_testClassInstance, &DelegateTestClass::II_Case1);
    }
    ~DelegateTestCase()
    {
      delete m_testClassInstance;
      m_testClassInstance = nullptr;
    }
  private: 
    void StartupTest_Implementation() override
    {
      assert(m_testClassInstance != nullptr);
    }

    void RunTest_Implementation() override
    {
      MDelegateHandle handle1 = (MultiDele1 += Dele3);
      MDelegateHandle handle2 = MultiDele1.AddDelegate(Dele3);

      std::cout << (handle1 == handle2) << std::endl;

      MultiDele1(34, 56);

      MultiDele1.Remove(handle1);
      MultiDele1.Invoke(56, 78);

      MultiDele1.Remove(handle2);
    }
  
  private:
    DelegateTestClass* m_testClassInstance;
    MDelegate<float(float)> Dele;
    MDelegate<float(float)> Dele2;
    MDelegate<void(int, int)> Dele3;
    MAction<void(int, int)> MultiDele1;
};

void func()
{
  std::cout << 42 << std::endl;
}

class AAA
{
  public:
    void func()
    {
      std::cout << "not const" << std::endl;
    }

    void funcConst() const
    {
      std::cout << "const" << std::endl;
    }
};


#if defined(CONSOLE_MAIN)
int main(int argc, char** argv)
#elif defined(WINDOWGUI_MAIN)
#include <windows.h>
#include <tchar.h>
int APIENTRY _tWinMain(IN MAYBE_UNUSED HINSTANCE hInstance, IN MAYBE_UNUSED HINSTANCE hPrevInstance, IN MAYBE_UNUSED LPTSTR lpCmdLinem, IN MAYBE_UNUSED int32 nShowCmd)
#endif
{
  MEngine::Core::IOutputInterface* logger = new MEngine::Core::ConsoleLogger();
  logger->Startup();
  logger->Serialize("Test log 1");
  logger->Serialize("Test log 2");
  logger->Flush();

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
    pTest->StartupTest_Interface();
    pTest->RunTest_Interface();
    delete pTest;

    pTest = new DelegateTestCase();
    pTest->StartupTest_Interface();
    pTest->RunTest_Interface();
    delete pTest;
  }

  int a;
  std::cin >> a;
  
  logger->Terminate();
  delete logger;

  return 0;
}

