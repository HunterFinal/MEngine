#pragma once

#ifndef _ME_OPENGLDRV_PLATFORMGLOBALS_
#define _ME_OPENGLDRV_PLATFORMGLOBALS_

namespace MEngine
{

namespace OpenGLDrv
{

// Setup the context to default state
// WARNING:Make sure you call this after an opengl context has been created
void GLSetupDefaultContextState();

}

}


#endif // _ME_OPENGLDRV_PLATFORMGLOBALS_