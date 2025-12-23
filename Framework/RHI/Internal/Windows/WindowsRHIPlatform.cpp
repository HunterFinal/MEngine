#include "WindowsRHIPlatform.h"
#include "Core/RHIBackend.h"

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
  // FIXME Temporary code
  delete RHIBackend;
}

} // namespace MEngine::RHI

} // namespace MEngine