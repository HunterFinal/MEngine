#ifndef _ME_LAUNCH_MAINLOOP_
#define _ME_LAUNCH_MAINLOOP_

#pragma once

namespace MEngine
{

namespace Launch
{

class MMainLoop
{
  public:
    virtual ~MMainLoop() = default;

  public:

    void Init();

    void Update();

    void Shutdown();
};

} // namespace MEngine::Launch

} // namespace MEngine

#endif // _ME_LAUNCH_MAINLOOP_