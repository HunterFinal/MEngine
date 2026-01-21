// MEngine entry point

#include <iostream>
#include "CoreAPI.h"
#include "OTGTAPI.h"
#include "ApplicationAPI.h"
#include "Event/WindowEventInstances.h"
#include "Windows/WindowsHeaderSet.h"

// TODO temp
#include "HAL/PlatformLowLevelAccessPort.h"
#include "CoreDynamicModule.h"

#include "Application/FutureFlexApplication.h"
#include "Widgets/FFWindow.h"

// TODO
#include "Modules/DynamicModuleManager.h"

// TODO RHI
#include "RHIGlobals.h"
#include "Resources/RHIBuffers.h"
#include "Resources/RHIShaders.h"
#include "Resources/RHIPipelineState.h"
#include "Resources/RHIVertexInputLayout.h"
#include "Resources/RHIBufferWriter.h"
#include "Resources/RHIDescriptors.h"
#include "Resources/RHIViewport.h"
#include "RHICommandList.h"
#include "RHIBackend.h"
#include "RHIContext.h"

#include <cstring>
#include <utility>
#include <conio.h>
#include <numbers>
#include <filesystem>

#define _CRT_SECURE_NO_WARNINGS

class MMathLibTestCase final : public OTGT::ITestCaseInterface
{
  public:
    MMathLibTestCase() = default;
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
      
      // Sign Test(Integer)
      me_assert(MMath::Sign(-2) == -1);
      me_assert(MMath::Sign(2) == 1);
      me_assert(MMath::Sign(0) == 0);

      me_assert(1 == MMath::Abs(1));
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
      std::cout << "class AAA : not const" << std::endl;
    }

    void funcConst() const
    {
      std::cout << "class AAA : const" << std::endl;
    }
};

static void RHITestInit();
static void RHITestRender_Triangle(HWND Handle, int32 Width, int32 Height);
static void RHITestRelease();

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

  // Calculate dot product
  // Result should be 0.5
  using MEngine::Math::MVector;
  MVector<float> vec3_1{1.0f, 0.0f, 0.0f};
  MVector<float> vec3_2{1.0f, std::numbers::sqrt3_v<float>, 0.0f};

  std::cout << "Result of dot product: " 
            << MVector<float>::DotProduct(vec3_1, vec3_2.GetNormalizedCopy()) 
            << std::endl;

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
    OTGT::ITestCaseInterface* pTest = new MMathLibTestCase();
    pTest->StartupTest_Interface();
    pTest->RunTest_Interface();
    delete pTest;

    pTest = new DelegateTestCase();
    pTest->StartupTest_Interface();
    pTest->RunTest_Interface();
    delete pTest;
  }

  {
    MEngine::Core::MWindowResizeEventInstance* p = new MEngine::Core::MWindowResizeEventInstance{};

    p->ResizeEvent.AddStatic(&func_out);
  
    p->InvokeEvent(100u, 200u);
    p->InvokeEvent(200u, 300u);
  
    delete p;
  }

  std::shared_ptr<MEngine::FutureFlex::FFWindow> testFFWindow = std::make_shared<MEngine::FutureFlex::FFWindow>();

  MEngine::FutureFlex::MFutureFlexApplication::Initialize();
  MEngine::FutureFlex::MFutureFlexApplication& FFApp = MEngine::FutureFlex::MFutureFlexApplication::GetInstance();
  FFApp.AssignExitRequestedDelegate(MEngine::Core::MDelegate<void()>::CreateStatic(&Globals::RequestApplicationExit));
  FFApp.AddWindow(testFFWindow);

  RHITestInit();

  while(!Globals::IsApplicationExitRequested())
  {
    FFApp.Update();
    IntSize windowSize = testFFWindow->GetNativeWindow()->GetWindowSize();
    RHITestRender_Triangle((HWND)testFFWindow->GetNativeWindow()->GetNativeWindowHandle(), windowSize.X, windowSize.Y);
  }

  RHITestRelease();

  FFApp.Terminate();
  
  MEngine::Core::MDebugger::ReleaseCurrentDebugger();
  
  int32 a;
  std::cin >> a;

  logger->Terminate();
  delete logger;

  return 0;
}

void RHITestInit()
{
  RHIGlobals::RHIInitialize();
}

void RHITestRender_Triangle(HWND Handle, int32 Width, int32 Height)
{
  me_assert(gRHIBackend != nullptr);
  // TODO Use RHI Here
  const float vertice[] =
  {
    -0.5f, -0.5f, 0.0f,
    0.5f,  -0.5f, 0.0f,
    0.0f,   0.5f, 0.0f
  };

  const char *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
  const char *fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}";

  MEngine::RHI::MRHIGraphicsCommandList* cmdList = new MEngine::RHI::MRHIGraphicsCommandList();
  MEngine::RHI::MRHIBufferDescriptor vertDesc{};
  vertDesc.BufferSize = sizeof(vertice);
  vertDesc.BufferUsage = static_cast<MEngine::RHI::EBufferUsageType>(::EnumCast(MEngine::RHI::EBufferUsageType::VertexBuffer) | ::EnumCast(MEngine::RHI::EBufferUsageType::Static));
  vertDesc.ElementStride = sizeof(vertice);
  vertDesc.BufferInitData = vertice;
  RHIBufferRefPtr vertBuffer{};

  // TODO This will create memory leak currently because of lacking of MRHIResource tracing process
  {
    MEngine::RHI::MRHIBufferWriter bufferWriter = cmdList->CreateBufferWriter(vertDesc);
    vertBuffer = bufferWriter.Finalize();
  }

  cmdList->SwitchPipeline(MEngine::RHI::ERHIPipeline::Graphics);

  RHIVertexShaderRefPtr vs = gRHIBackend->RHICreateVertexShader(std::span<const uint8>{(uint8*)vertexShaderSource , ::strlen(vertexShaderSource) + 1});
  RHIPixelShaderRefPtr ps = gRHIBackend->RHICreatePixelShader(std::span<const uint8>{(uint8*)fragmentShaderSource , ::strlen(fragmentShaderSource) + 1});
  
  // Input layout and buffer bindings
  std::vector<MEngine::RHI::MRHIVertexElement> vertexElems{};
  MEngine::RHI::MRHIVertexElement elem{};
  elem.Offset = 0;
  elem.Format = MEngine::RHI::ERHIVertexFormat::Float3;
  elem.Location = 0;
  elem.SlotIndex = 0;
  vertexElems.emplace_back(elem);

  MEngine::RHI::MRHIVertexBinding bindings[MEngine::RHI::MaxVertexBindingCount];
  bindings[0].Stride = sizeof(float) * 3;
  bindings[0].InputRate = MEngine::RHI::ERHIVertexInputRate::PerVertex;
  MEngine::RHI::MRHIVertexBindingDescriptor bindingDesc{1, bindings};

  RHIVertexInputLayoutRefPtr inputLayout = gRHIBackend->RHICreateVertexInputLayout(vertexElems, bindingDesc);

  // PSO
  MEngine::RHI::MRHIGraphicsPipelineStateDescriptor psoDesc{};
  psoDesc.RHIVertexShader = vs;
  psoDesc.RHIPixelShader  = ps;
  psoDesc.RHIInputLayout  = inputLayout;
  psoDesc.PrimitiveType   = MEngine::RHI::EPrimitiveTopologyType::TriangleList;
  RHIGraphicsPipelineStateRefPtr graphicsPSO = gRHIBackend->RHICreateGraphicsPSO(psoDesc);

  RHIViewportRefPtr viewport = gRHIBackend->RHICreateViewport(Handle, Width, Height);

  cmdList->SetGraphicsPipelineState(graphicsPSO);
  cmdList->SetVertexBufferBinding(0, vertBuffer, bindings[0]);

  cmdList->StartDrawingViewport(viewport);

  // Draw triangles
  cmdList->DrawPrimitive(0, 1, 1);

  // Exec commands
  cmdList->ExecuteCommands();

  cmdList->EndDrawingViewport(viewport);

  delete cmdList;
}

void RHITestRelease()
{
  RHIGlobals::RHIShutdown();
}