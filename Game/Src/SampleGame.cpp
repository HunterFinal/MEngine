#include "SampleGame.h"
#include <iostream>

using namespace std;

extern "C" IApplicationInterface* GenerateAPP()
{
  return new SampleGame{};
}

SampleGame::~SampleGame()
{
  Terminate();
}

void SampleGame::Startup()
{

}

void SampleGame::Update(float DeltaTime)
{

}

void SampleGame::Terminate()
{

}