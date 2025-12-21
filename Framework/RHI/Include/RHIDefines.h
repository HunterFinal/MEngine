#pragma once

#ifndef _ME_RHI_DEFINES_
#define _ME_RHI_DEFINES_

#include "HAL/Platform.h"
#include "Misc/CoreDefines.h"

#ifdef RHI_EXPORT
#define RHI_API DLLEXPORT
#else
#define RHI_API DLLIMPORT
#endif // RHI_EXPORT

#endif // _ME_RHI_DEFINES_