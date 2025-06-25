#pragma once

#ifndef _ME_APP_FUNC_SYMBOL_HELPERS_
#define _ME_APP_FUNC_SYMBOL_HELPERS_

#define ME_EXTERN_C_START ME_EXTERN_C_START_INNER
#define ME_EXTERN_C_END ME_EXTERN_C_END_INNER

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


#endif // _ME_APP_FUNC_SYMBOL_HELPERS_