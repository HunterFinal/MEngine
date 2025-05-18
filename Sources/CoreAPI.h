// MEngine force include header

#ifdef _WIN32
#pragma once
#endif

#ifndef MENGINE_CORE_INCLUDE
#define MENGINE_CORE_INCLUDE

#include "Macro/CPPVerMacro.h"

// 低レイヤーヘッダ
#include "HAL/Platform.h"
#include "Misc/CoreDefines.h"

// よく使われるヘッダ
#include "Macro/ClassMacroHelpers.h"
#include "Macro/AssertionMacros.h"
#include "Templates/METypeTraits.h"
#include "Math/MEngineMathUtility.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"

#endif // MENGINE_CORE_INCLUDE