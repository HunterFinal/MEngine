#pragma once

#ifndef _ME_COREOBJECT_DEFINES_
#define _ME_COREOBJECT_DEFINES_

#include "CoreDefines.h"
#include "HAL/Platform.h"

#ifdef COREOBJECT_EXPORT
#define COREOBJECT_API DLLEXPORT
#else
#define COREOBJECT_API DLLIMPORT
#endif  // COREOBJECT_EXPORT

#endif // _ME_COREOBJECT_DEFINES_