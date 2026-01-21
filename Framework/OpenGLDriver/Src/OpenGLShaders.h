#pragma once

#ifndef _ME_OPENGLDRV_SHADERS_
#define _ME_OPENGLDRV_SHADERS_

#include "OpenGLResource.h"

#include "Resources/RHIShaders.h"

// TODO
#include <span>

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLLinkedShaderProgram;

struct MOpenGLCachedShaderKey
{
  friend struct MOpenGLCachedShaderKeyHash;

  MOpenGLCachedShaderKey()
    : m_shaderType{0}
    , m_glslCodeSize{0}
    , m_glslCodeHash{0}
  { }
  MOpenGLCachedShaderKey(IN GLenum Type, IN uint64 CodeSize, IN uint64 CodeHash)
    : m_shaderType{Type}
    , m_glslCodeSize{CodeSize}
    , m_glslCodeHash{CodeHash}
  { }

  friend bool operator==(IN const MOpenGLCachedShaderKey& Lhs, IN const MOpenGLCachedShaderKey& Rhs);
  friend bool operator!=(IN const MOpenGLCachedShaderKey& Lhs, IN const MOpenGLCachedShaderKey& Rhs);

  uint64 GetHash() const { return m_glslCodeHash; }

private:
  GLenum m_shaderType;
  uint64 m_glslCodeSize;
  uint64 m_glslCodeHash;
};

class MOpenGLShader
{

protected:
  MOpenGLShader(IN std::span<const uint8> ShaderCode, GLenum ShaderType);

public:
  void Compile();

  GLuint GLResource()                     const { return m_nativeResource.Resource   ; }
  GLenum GLShaderType()                   const { return m_nativeResource.Type       ; }
  MOpenGLCachedShaderKey GLSLCodeKey()    const { return m_GLSLCodeKey               ; }

private:
  MOpenGLCachedShaderKey m_GLSLCodeKey;
  MOpenGLResource m_nativeResource;
};

template<typename RHIShaderBaseType, GLenum GLShaderTypeEnum>
Requires_Derived_From(RHIShaderBaseType, MEngine::RHI::MRHIShader)
class TOpenGLShader : public RHIShaderBaseType, public MOpenGLShader
{
  public:
    TOpenGLShader(IN std::span<const uint8> ShaderCode)
      : MOpenGLShader{ShaderCode, GLShaderTypeEnum}
    {}

    uint64 GetGLHash() const
    {
      return MOpenGLShader::GLSLCodeKey().GetHash();
    }
};

// TODO
using MOpenGLVertexShader = TOpenGLShader<MEngine::RHI::MRHIVertexShader, GL_VERTEX_SHADER>;
using MOpenGLPixelShader = TOpenGLShader<MEngine::RHI::MRHIPixelShader, GL_FRAGMENT_SHADER>;

struct MOpenGLCachedLinkedShaderProgramKey
{

friend struct MOpenGLCachedLinkedShaderProgramKeyHash;
  
public:
  MOpenGLCachedLinkedShaderProgramKey();
  MOpenGLCachedLinkedShaderProgramKey(MOpenGLVertexShader* GLVertexShader, MOpenGLPixelShader* GLPixelShader);

  friend bool operator==(const MOpenGLCachedLinkedShaderProgramKey& Lhs, const MOpenGLCachedLinkedShaderProgramKey& Rhs);
  friend bool operator!=(const MOpenGLCachedLinkedShaderProgramKey& Lhs, const MOpenGLCachedLinkedShaderProgramKey& Rhs);

  uint64 ShaderHashes[MEngine::RHI::MAX_STAGE_NUM];
};

} // namespace MEngine::OpenGLDrv

} // namespace MEngine

TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::OpenGLDrv::MOpenGLVertexShader>, GLVertexShaderRefPtr);
TYPEDEF(MEngine::RHI::TRHIRefCountPtr<MEngine::OpenGLDrv::MOpenGLPixelShader>,  GLPixelShaderRefPtr);

#endif // _ME_OPENGLDRV_SHADERS_