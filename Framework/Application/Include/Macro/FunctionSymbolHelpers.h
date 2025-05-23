#pragma once

#ifndef APP_FUNC_SYMBOL_HELPERS
#define APP_FUNC_SYMBOL_HELPERS

#ifdef __cplusplus
#define ME_EXTERN_C_START_INNER \
  extern "C" \
  {

#define ME_EXTERN_C_END_INNER \
  }
#else
#define ME_EXTERN_C_START_INNER
#define ME_EXTERN_C_END_INNER
#endif

#define ME_EXTERN_C_START ME_EXTERN_C_START_INNER
#define ME_EXTERN_C_END ME_EXTERN_C_END_INNER

#endif // APP_FUNC_SYMBOL_HELPERS