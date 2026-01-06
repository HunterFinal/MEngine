#include "OpenGLDriverRHIModule.h"
#include "OpenGLDriverRHI.h"

MENGINE_IMPLEMENT_DYNAMIC_MODULE(MEngine::OpenGLDrv::MOpenGLDriverRHIModule, OpenGLDriver);

namespace MEngine
{

namespace OpenGLDrv
{

bool MOpenGLDriverRHIModule::IsSupported() const
{
  return true;
}

MEngine::RHI::IRHIBackend* MOpenGLDriverRHIModule::CreateRHIBackend()
{
  return new MEngine::OpenGLDrv::MOpenGLRHIBackend{};
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine