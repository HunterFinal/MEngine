#include "PlatformOpenGLDriverGlobals.h"
#include "OpenGLUtils.h"
#include "HALOpenGLThirdParty.h"

#include "RHITypes.h"

namespace MEngine
{

namespace OpenGLDrv
{

void GLSetupDefaultContextState()
{
  glDisable(GL_DITHER);
}

GLenum PrimitiveRHIToGL(IN MEngine::RHI::EPrimitiveTopologyType RHIPrimitiveType)
{
  using enum MEngine::RHI::EPrimitiveTopologyType;
  switch (RHIPrimitiveType)
  {
    case TriangleList:
      return GL_TRIANGLES;

    default:
    {
      // Need implement more
      me_assert(false);
      return 0;
    }
  }
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine