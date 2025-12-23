// MEngine force include header
#pragma once

#ifndef MENGINE_CORE_INCLUDE
#define MENGINE_CORE_INCLUDE

#include "CoreDefines.h"
#include "Macro/CPPVerMacro.h"
#include "Macro/DeprecationMacro.h"

// 低レイヤーヘッダ
#include "Globals/CoreGlobals.h"
#include "HAL/Platform.h"

// よく使われるヘッダ
#include "Macro/ClassMacroHelpers.h"
#include "Macro/AssertionMacros.h"
#include "Templates/METypeTraits.h"
#include "Math/MEngineMathUtility.h"
#include "Delegates/Delegate.h"

// Math
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"

// アプリケーション
#include "Application/ApplicationAPI.h"

// ログ
#include "Logging/IOutputInterface.h"
#include "Logging/ConsoleLogger.h"

#endif // MENGINE_CORE_INCLUDE