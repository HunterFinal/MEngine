#pragma once

#ifndef _ME_OPENGLDRV_COMMANDS_
#define _ME_OPENGLDRV_COMMANDS_

#include "RHICommand.h"

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLBuffer;

class MOpenGLBufferInitializationCommand : public MEngine::RHI::TRHICommand<MOpenGLBufferInitializationCommand>
{
  public:
    MOpenGLBufferInitializationCommand(IN MOpenGLBuffer* InBuffer, IN const void* InData);
    ~MOpenGLBufferInitializationCommand();

    void Execute(OUT MEngine::RHI::MRHICommandList& CommandList);

  private:
    MOpenGLBuffer* m_buffer;
    const void* m_data;

};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine



#endif // _ME_OPENGLDRV_COMMANDS_