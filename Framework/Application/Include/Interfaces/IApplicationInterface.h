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
    virtual void Update(float DeltaTime) {};
    virtual void Terminate() {};
};

extern "C" APP_API IApplicationInterface* GenerateAPP(); 

#endif // ME_APP_INTERFACE