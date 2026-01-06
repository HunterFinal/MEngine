#pragma once

#ifndef _ME_CORE_STANDARDMACROS_
#define _ME_CORE_STANDARDMACROS_

#include "HAL/Platform.h"

// Returns a uint8(&)[n + 1] array (No implementation function)
template <typename Type, SIZE_T n>
uint8 (&ArrayCountHelper(const Type(&)[n]))[n + 1];

#define SIZE_OF_ARRAY(array) (sizeof(ArrayCountHelper(array)) - 1)

#endif // _ME_CORE_STANDARDMACROS_