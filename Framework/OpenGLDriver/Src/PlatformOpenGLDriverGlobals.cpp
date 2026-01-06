#include "PlatformOpenGLDriverGlobals.h"
#include "OpenGLUtils.h"
#include "HALOpenGLThirdParty.h"

namespace MEngine
{

namespace OpenGLDrv
{

void GLSetupDefaultContextState()
{
  // Check if context has been created
  OPENGL_STATE_CHECK();

  glDisable(GL_DITHER);
}

} // namespace MEngine::OpenGLDrv

} // namespace MEngine