
#include <iostream>

#include "CoreAPI.h"

#include "ApplicationAPI.h"
#include "Event/WindowEventInstances.h"
#include "Windows/WindowsHeaderSet.h"

// TODO temp
#include "HAL/PlatformLowLevelAccessPort.h"
#include "CoreDynamicModule.h"

#include "Application/FutureFlexApplication.h"
#include "Widgets/FFWindow.h"

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
#include <numbers>

#define _CRT_SECURE_NO_WARNINGS

namespace
{
  void StartupEnvironment();
  void RHITestRender_Triangle(void* Handle, int32 Width, int32 Height);
  MEngine::Core::IOutputInterface* GLogger;
  std::shared_ptr<MEngine::FutureFlex::FFWindow> GMainWindow;
}

bool StartupWindows(IN HINSTANCE hInstance, IN MAYBE_UNUSED int32 nCmdShow)
{
  StartupEnvironment();

  gHInstance = hInstance;

  GLogger = new MEngine::Core::ConsoleLogger();
  GLogger->Startup();
  GLogger->Serialize("Test log 1");
  GLogger->Serialize("Test log 2");
  GLogger->Flush();
  
  MEngine::Core::MDebugger::CreateDefaultDebugger();
  
  MEngine::FutureFlex::MFutureFlexApplication::Initialize();
  GMainWindow = std::make_shared<MEngine::FutureFlex::FFWindow>();
  MEngine::FutureFlex::MFutureFlexApplication& FFApp = MEngine::FutureFlex::MFutureFlexApplication::GetInstance();
  FFApp.AssignExitRequestedDelegate(MEngine::Core::MDelegate<void()>::CreateStatic(&Globals::RequestApplicationExit));
  FFApp.AddWindow(GMainWindow);

  RHIGlobals::RHIInitialize();
  return true;
}

int32 RunWindows(IN MAYBE_UNUSED HINSTANCE hInstance, IN MAYBE_UNUSED int32 nCmdShow)
{

  auto& app = MEngine::FutureFlex::MFutureFlexApplication::GetInstance();

  while(!Globals::IsApplicationExitRequested())
  {
    app.Update();
    IntSize windowSize = GMainWindow->GetNativeWindow()->GetWindowSize();
    RHITestRender_Triangle(GMainWindow->GetNativeWindow()->GetNativeWindowHandle(), windowSize.X, windowSize.Y);
  }

  return 0;
}

void ShutdownWindows()
{
  static bool bIsShutdown = false;
  if (bIsShutdown)
  {
    return;
  }

  MEngine::FutureFlex::MFutureFlexApplication::GetInstance().Terminate();
  RHIGlobals::RHIShutdown();
  MEngine::Core::MDebugger::ReleaseCurrentDebugger();

  me_assert(GLogger != nullptr);
  GLogger->Terminate();
  delete GLogger;
  GLogger = nullptr;

  GMainWindow.reset();

  bIsShutdown = true;
}


namespace
{
  void StartupEnvironment()
  {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  }

  void RHITestRender_Triangle(void* Handle, int32 Width, int32 Height)
  {
    me_assert(gRHIBackend != nullptr);

    // TODO Use RHI Here
    const float vertice[] =
    {
      -0.5f, -0.2f, 0.0f,
      0.5f,  -0.5f, 0.0f,
      0.0f,   0.5f, 0.0f
    };

    const char *vertexShaderSource = "#version 460 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
    const char *fragmentShaderSource = "#version 460 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";

    MEngine::RHI::MRHIGraphicsCommandList* cmdList = new MEngine::RHI::MRHIGraphicsCommandList();
    cmdList->SwitchPipeline(MEngine::RHI::ERHIPipeline::Graphics);
    RHIViewportRefPtr viewport = gRHIBackend->RHICreateViewport(Handle, Width, Height);
    cmdList->StartDrawingViewport(viewport);

    // Describe usage of vertex buffer
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

    // Shader
    RHIVertexShaderRefPtr vs = gRHIBackend->RHICreateVertexShader(std::span<const uint8>{(uint8*)vertexShaderSource , ::strlen(vertexShaderSource) + 1});
    RHIPixelShaderRefPtr ps = gRHIBackend->RHICreatePixelShader(std::span<const uint8>{(uint8*)fragmentShaderSource , ::strlen(fragmentShaderSource) + 1});
    
    // Describe input layout of vertex
    std::vector<MEngine::RHI::MRHIVertexElement> vertexElems{};
    MEngine::RHI::MRHIVertexElement elem
    {
      .Offset = 0,
      .Format = MEngine::RHI::ERHIVertexFormat::Float3,
      .Location = 0,
      .SlotIndex = 0,
    };

    vertexElems.emplace_back(elem);

    MEngine::RHI::MRHIVertexBinding bindings[MEngine::RHI::MaxVertexBindingCount]
    {
      // index 0
      {
        .Stride = sizeof(float) * 3, 
        .InputRate = MEngine::RHI::ERHIVertexInputRate::PerVertex
      },
    };

    MEngine::RHI::MRHIVertexBindingDescriptor bindingDesc{1, bindings};
    
    RHIVertexInputLayoutRefPtr inputLayout = gRHIBackend->RHICreateVertexInputLayout(vertexElems, bindingDesc);
    
    // PSO
    MEngine::RHI::MRHIGraphicsPipelineStateDescriptor psoDesc{};
    psoDesc.RHIVertexShader = vs;
    psoDesc.RHIPixelShader  = ps;
    psoDesc.RHIInputLayout  = inputLayout;
    psoDesc.PrimitiveType   = MEngine::RHI::EPrimitiveTopologyType::TriangleList;
    RHIGraphicsPipelineStateRefPtr graphicsPSO = gRHIBackend->RHICreateGraphicsPSO(psoDesc);
    
    cmdList->SetGraphicsPipelineState(graphicsPSO);
    cmdList->SetVertexBufferBinding(0, vertBuffer, bindings[0]);

    // Draw triangles
    cmdList->DrawPrimitive(0, 1, 1);
    // Exec commands
    cmdList->ExecuteCommands();

    cmdList->EndDrawingViewport(viewport);

    delete cmdList;
  }
}



