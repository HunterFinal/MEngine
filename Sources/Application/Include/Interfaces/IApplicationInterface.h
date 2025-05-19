#ifdef _WIN32
#pragma once
#endif

#ifndef ME_APP_INTERFACE
#define ME_APP_INTERFACE

#include "Include/ApplicationDefines.h" 

struct APP_API IApplicationInterface
{
  public:
    virtual ~IApplicationInterface() = default;

  public:
    virtual void Startup() {};
    virtual void Update(float DeltaTime) {};
    virtual void Terminate() {};
};

APP_API FORCEINLINE IApplicationInterface* GenerateAPP(); 

#endif // ME_APP_INTERFACE