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
  private:
    int result;
};

void func(int a, int b)
{
  std::cout << a / b << std::endl;
}

class DelegateTestCase final : public OTGT::ITestCaseInterface
{
 public:
    DelegateTestCase()
      : m_testClassInstance(new DelegateTestClass())
      , m_v_ii_staticFuncDele1{&func}
      , m_v_ii_classMemDele1{m_testClassInstance, &DelegateTestClass::VII_Case1}
      , m_i_v_const_classMemDele2{m_testClassInstance, &DelegateTestClass::I_ConstCase1}
    {
      Dele.BindStatic(&MMath::Sign);
      Dele2.BindClass(m_testClassInstance, &DelegateTestClass::FF_Case1);
      std::cout << Dele2(3.14f) << std::endl;
            
      Dele2.BindClass(m_testClassInstance, &DelegateTestClass::FF_ConstCase1);
    }
    ~DelegateTestCase()
    {
      delete m_testClassInstance;
      m_testClassInstance = nullptr;
    }
  private: 
    void StartupTest_Implementation() const override
    {
      assert(m_testClassInstance != nullptr);

    }

    void RunTest_Implementation() const override
    {
      m_v_ii_staticFuncDele1(1,2);
      m_v_ii_staticFuncDele1.Invoke(2,1);

      m_v_ii_classMemDele1(42, 56);
      assert(m_i_v_const_classMemDele2.Invoke() == (42 * 56));

      m_v_ii_classMemDele1.Invoke(1234, 5678);
      assert(m_i_v_const_classMemDele2() == (1234 * 5678));
      assert(Dele.Invoke(-2.0f) == -1.0f);
      std::cout << Dele.Invoke(3.1415926535f) << std::endl;

      std::cout << Dele2(1234.f) << std::endl;
    }
  
  private:
    DelegateTestClass* m_testClassInstance;
    MEngine::Core::MStaticFunctionDelegateInstance<void(int,int)> m_v_ii_staticFuncDele1;
    MEngine::Core::MClassMethodDelegateInstance<false, DelegateTestClass, void(int, int)> m_v_ii_classMemDele1;
    MEngine::Core::MClassMethodDelegateInstance<true, DelegateTestClass, int()> m_i_v_const_classMemDele2;
    MEngine::Core::MDelegate<float(float)> Dele;
    MEngine::Core::MDelegate<float(float)> Dele2;
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

