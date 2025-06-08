// MEngine class helper macro definitions
#pragma once

#ifndef _ME_CLASS_MACRO_HELPER_
#define _ME_CLASS_MACRO_HELPER_

#include "TypeAliasMacro.h"

#define GENERATE_CLASS_DEF(Class) GENERATE_CLASS_DEF_INNER(Class)
#define GENERATE_CLASS_DEF_INNER(Class) \
    TYPEDEF(Class, ThisClass);

#endif // _ME_CLASS_MACRO_HELPER_