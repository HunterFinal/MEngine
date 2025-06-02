#include "Event/WindowEventInstances.h"
#include <iostream>

namespace MEngine
{
  namespace Core
  {
    MWindowResizeEventInstance::MWindowResizeEventInstance()
    {}

    MWindowResizeEventInstance::~MWindowResizeEventInstance()
    {}

    void MWindowResizeEventInstance::Invoke(IN uint32 Width, IN uint32 Height)
    {
      using namespace std;

      if (ResizeEvent.IsBound())
      {
        ResizeEvent.Invoke(Width, Height);
      }
    }
  }
}