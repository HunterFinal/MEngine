#ifdef _WIN32
#pragma once
#endif

#ifndef SAMPLE_GAME
#define SAMPLE_GAME

#include "Interfaces/IApplicationInterface.h"
#include "GameDefines.h"

class GAME_API SampleGame final : public IApplicationInterface
{
  public:
    ~SampleGame();
    void Startup() override final;
    void Update(float DeltaTime) override final;
    void Terminate() override final;
};

#endif // SAMPLE_GAME