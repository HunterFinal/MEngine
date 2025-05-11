#ifdef _WIN32
#pragma once
#endif


#ifndef MENGINE_TYPE_TRAITS
#define MENGINE_TYPE_TRAITS

#include <type_traits>

#define TEMPLATE_CONDITION(...) typename std::enable_if_t<__VA_ARGS__, int> = 0

#endif // MENGINE_TYPE_TRAITS