#include "WindowsRHIPlatform.h"

namespace MEngine
{

namespace RHI
{

IRHIBackend* MWindowsRHIPlatform::CreateRHIBackend()
{
  return nullptr;
}

void MWindowsRHIPlatform::ShutdownRHIBackend()
{

}

} // namespace MEngine::RHI

} // namespace MEngine