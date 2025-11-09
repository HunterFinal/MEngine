#pragma once

#ifndef _ME_RUNTIME_ECSCORE_CONFIG_
#define _ME_RUNTIME_ECSCORE_CONFIG_

#include "Misc/CoreDefines.h"

#ifndef ECS_CORE_DLL_BUILD
#define ECSCORE_API __declspec(dllexport)
#else
#define ECSCORE_API __declspec(dllimport)
#endif // ECS_CORE_DLL_BUILD

#endif // _ME_RUNTIME_ECSCORE_CONFIG_