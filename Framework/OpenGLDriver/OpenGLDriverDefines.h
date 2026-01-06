#pragma once

#ifndef _ME_OPENGLDRV_DEFINES_
#define _ME_OPENGLDRV_DEFINES_

#include "CoreDefines.h"

#ifdef OPENGLDRV_EXPORT
#define OPENGLDRV_API DLLEXPORT
#else
#define OPENGLDRV_API DLLIMPORT
#endif // RHI_EXPORT

#endif // _ME_OPENGLDRV_DEFINES_