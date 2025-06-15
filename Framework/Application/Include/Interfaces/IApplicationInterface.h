#pragma once

#ifndef _ME_APP_APPLICATION_INTERFACE_
#define _ME_APP_APPLICATION_INTERFACE_

#include "Macro/ApplicationDefines.h"
#include "Macro/FunctionSymbolHelpers.h" 

struct APP_API IApplicationInterface
{
  public:
    virtual ~IApplicationInterface() = default;

  public:
    virtual void Startup() {};
    virtual void Update(IN [[maybe_unused]] float DeltaTime) {};
    virtual void Terminate() {};
};

ME_EXTERN_C_START
APP_API IApplicationInterface* GenerateAPP(); 
ME_EXTERN_C_END

#endif // _ME_APP_APPLICATION_INTERFACE_