#pragma once

#ifndef ME_APP_INTERFACE
#define ME_APP_INTERFACE

#include "Macro/ApplicationDefines.h" 

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

#endif // ME_APP_INTERFACE