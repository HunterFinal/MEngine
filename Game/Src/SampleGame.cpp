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
  cout << "SampleGame Startup" << endl;
}

void SampleGame::Update(float DeltaTime)
{
  cout << "SampleGame Update" << endl;
}

void SampleGame::Terminate()
{
  cout << "SampleGame Terminate" << endl;
}