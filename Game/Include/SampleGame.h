#pragma once

#ifndef SAMPLE_GAME
#define SAMPLE_GAME

#include "GameDefines.h"

class GAME_API SampleGame final : public IApplicationInterface
{
  public:
    ~SampleGame();
    void Startup() override final;
    void Update(IN float DeltaTime) override final;
    void Terminate() override final;

  private:
    
};

#endif // SAMPLE_GAME