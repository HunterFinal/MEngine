#pragma once

#ifndef _ME_RUNTIME_FUTURE_FLEX_CORE_API_
#define _ME_RUNTIME_FUTURE_FLEX_CORE_API_

#ifdef RUNTIME_DLL_BUILD
#define RUNTIME_API __declspec(dllexport)
#else
#define RUNTIME_API __declspec(dllimport)
#endif // RUNTIME_DLL_BUILD

#endif // _ME_RUNTIME_FUTURE_FLEX_CORE_API_
