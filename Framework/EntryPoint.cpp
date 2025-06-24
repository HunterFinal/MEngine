// MEngine entry point

#include <iostream>
#include "CoreAPI.h"
#include "OTGTAPI.h"
#include "ApplicationAPI.h"
#include "Event/WindowEventInstances.h"
#include "HAL/PlatformLowLevelAccessPort.h"
#include "Windows/WindowsHeaderSet.h"

#include "Application/FutureFlexApplication.h"
#include "Widgets/FFWindow.h"

// TODO
#include <spdlog/fmt/bundled/format.h>
#include <cstring>
#include <utility>

#define _CRT_SECURE_NO_WARNINGS

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
      me_assert(MMath::Abs(-2) == 2);
      me_assert(MMath::Abs(2) == 2);
      // Abs Test(Floating-type)
      me_assert(MMath::IsNearlyEquals(MMath::Abs(-2.2), 2.2));
      me_assert(MMath::IsNearlyEquals(MMath::Abs(2.2), 2.2));
      me_assert(MMath::IsNearlyEquals(MMath::Abs(-1.11f), 1.11f));
      me_assert(MMath::IsNearlyEquals(MMath::Abs(1.11f), 1.11f));
      // IsNearlyZero Test
      me_assert(MMath::IsNearlyZero(0.000000001f));
      me_assert(MMath::IsNearlyZero(0.000000001));
      me_assert(MMath::IsNearlyZero(0.000000001l));
      me_assert(MMath::IsNearlyZero(0.0f));
      me_assert(MMath::IsNearlyZero(0.0));
      me_assert(MMath::IsNearlyZero(0.0l));

      // Max Text(Integer)
      me_assert(MMath::Max(22, 33) == 33);
      me_assert(MMath::Max(0, 0) == 0);
      me_assert(MMath::Max(-22, -33) == -22);

      // 

      
      // Sign Test(Integer)
      me_assert(MMath::Sign(-2) == -1);
      me_assert(MMath::Sign(2) == 1);
      me_assert(MMath::Sign(0) == 0);

      me_assert(1 == MMath::Abs(1));
      me_assert(true);
      me_assert(MMath::Sign(0) == 0);
      
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

      MultiDele1.AddDelegate(MDelegate<void(int, int)>::CreateStatic(&func2));
      MultiDele1.AddDelegate(MDelegate<void(int, int)>::CreateClass(m_testClassInstance, &DelegateTestClass::II_Case1));
      MultiDele1(34, 56);

      MultiDele1.Invoke(56, 78);

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

void func_out(uint32 a, uint32 b)
{
  std::cout << "Test" << a << "tseT" << b;
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

#if 0
int main(int argc, char** argv)
#else
int32 WINAPI WinMain(IN MAYBE_UNUSED HINSTANCE hInstance, IN MAYBE_UNUSED HINSTANCE hPrevInstance, IN MAYBE_UNUSED /**LPSTR */ char* lpCmdLine, IN MAYBE_UNUSED int32 nShowCmd)
#endif
{
  // TODO
  gHInstance = hInstance;

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

  MEngine::Core::MDebugger::CreateDefaultDebugger();

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

  MEngine::Core::MWindowResizeEventInstance* p;
  p = new MEngine::Core::MWindowResizeEventInstance{};

  p->ResizeEvent.AddStatic(&func_out);

  p->InvokeEvent(100u, 200u);
  p->InvokeEvent(200u, 300u);

  delete p;

  auto testFFWindow = std::make_shared<MEngine::FutureFlex::FFWindow>();

  MEngine::FutureFlex::MFutureFlexApplication::GetInstance().Initialize();
  MEngine::FutureFlex::MFutureFlexApplication::GetInstance().AddWindow(testFFWindow);

  while(!Globals::IsApplicationExitRequested())
  {
    MEngine::FutureFlex::MFutureFlexApplication::GetInstance().Update();
  }

  logger->Terminate();
  delete logger;
  
  MEngine::Core::MDebugger::ReleaseCurrentDebugger();
  
  Matrix44 testM(Vector4(1.f, 1.f, 1.f, 1.f), Vector4(2.f, 5.f, 6.f, 8.f), Vector4(9.f, 3.f, 66.f, 12.f), Vector4(13.f, 15.f, 25.f, 20.f));
  
  std::cout << testM.GetDeterminant() << std::endl;
  
  int a;
  std::cin >> a;

  delete 
  return 0;
}

