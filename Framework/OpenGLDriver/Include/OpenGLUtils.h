#pragma once

#ifndef _ME_OPENGLDRV_UTILS_
#define _ME_OPENGLDRV_UTILS_

#include "Macro/AssertionMacros.h"

// Forward declaration
namespace MEngine
{
namespace OpenGLDrv
{
  extern bool GLHasRenderingContext();
}  
}

#define OPENGL_STATE_CHECK() \
  do \
  { \
    if (!MEngine::OpenGLDrv::GLHasRenderingContext()) \
    { \
      me_assert(false); \
    } \
  } while (false);
  

#ifndef OPENGL_STATE_CHECK()
#define OPENGL_STATE_CHECK()
#endif

#endif // _ME_OPENGLDRV_UTILS_