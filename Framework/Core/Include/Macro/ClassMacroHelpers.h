// MEngine class helper macro definitions
#pragma once

#ifndef MENGINE_CLASS_MACRO_HELPER
#define MENGINE_CLASS_MACRO_HELPER

#include "TypeAliasMacro.h"

#define GENERATE_CLASS_DEF(Class) GENERATE_CLASS_DEF_INNER(Class)
#define GENERATE_CLASS_DEF_INNER(Class) \
    TYPEDEF(Class, ThisClass);

#endif // MENGINE_CLASS_MACRO_HELPER