#include "WindowsRHIPlatform.h"

namespace MEngine
{

namespace RHI
{

IRHIBackend* MWindowsRHIPlatform::CreateRHIBackend()
{
  return nullptr;
}

void MWindowsRHIPlatform::ShutdownRHIBackend(IN IRHIBackend* RHIBackend)
{
  
}

} // namespace MEngine::RHI

} // namespace MEngine