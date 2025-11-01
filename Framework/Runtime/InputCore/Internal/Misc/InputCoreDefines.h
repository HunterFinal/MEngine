#pragma once

#ifndef _ME_INPUTCORE_INTERNAL_DEFINES_
#define _ME_INPUTCORE_INTERNAL_DEFINES_

#ifdef INPUT_CORE_DLL_BUILD
#define INPUTCORE_API __declspec(dllexport)
#else
#define INPUTCORE_API __declspec(dllimport)
#endif // INPUT_CORE_DLL_BUILD

#endif // _ME_INPUTCORE_INTERNAL_DEFINES_