#pragma once

#ifndef _ME_OPENGLDRV_RESOURCE_
#define _ME_OPENGLDRV_RESOURCE_

#include "GenericPlatformOpenGLDriver.h"
#include "Utils/RHIRefCountPtr.h"
#include "Resources/RHIBuffers.h"
#include "Templates/TypeCast.h"

namespace MEngine
{

namespace OpenGLDrv
{
  class MOpenGLResource
  {
    private:
      friend class MOpenGLBuffer;

      explicit MOpenGLResource(IN GLenum InType)
        : Type{InType}
        , Resource{0}
      {}

    public:
      void Bind();
      void OnDeleted();

      GLenum Type;
      GLuint Resource;
  };

  class MOpenGLBuffer : public MEngine::RHI::MRHIBuffer
  {
    public:
      MOpenGLBuffer(IN MEngine::RHI::MRHICommandList* CmdList, IN GLenum BufferType, IN const MEngine::RHI::MRHIBufferDescriptor& Descriptor, IN const void* Data);      
      virtual ~MOpenGLBuffer();

      void BindToOpenGL();

      void* Map(IN uint32 InSize, IN uint32 InOffset);

      void Unmap();

      GLenum GLType() { return m_nativeResource.Type; }
      GLenum GLUsage() { return IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW; } 
      GLuint GLResource() { return m_nativeResource.Resource; }
      GLuint* GLResourceAddress() { return &(m_nativeResource.Resource); }

      bool IsDynamic() const { return (::EnumCast(GetDesc().BufferUsage) & ::EnumCast(MEngine::RHI::EBufferUsageType::Dynamic)) != 0; }

    private:
      void ReleaseResource();

    private:
      struct MappingInfo
      {
        void* MapData = nullptr;
        uint32 MapSize = 0;
        uint32 MapOffset = 0;
        bool bWasMapDataAllocated = false;
      } m_mappingState;

      MOpenGLResource m_nativeResource;
      bool m_bIsMapping;
  };
}

}

#endif // _ME_OPENGLDRV_RESOURCE_