#include "OpenGLShaders.h"
#include "OpenGLUtils.h"
#include "OpenGLDriverRHI.h"

#include "HAL/PlatformStringUtility.h"
#include "Misc/HashFunctions.h"

#include <unordered_map>
#include <vector>

// TODO
#include <iostream>

namespace
{
  void AppendGLSLString(OUT std::vector<ANSICHAR>& Dest, IN const ANSICHAR* const Src);

  bool VerifyShaderCompilationStatus(IN GLuint ShaderResource);
  bool VerifyProgramLinkStatus(IN GLuint ProgramResource);
  void LogShaderCompileFailure(IN GLuint ShaderResource);
  void LogProgramLinkFailure(IN GLuint ProgramResource);
}

namespace MEngine
{

namespace OpenGLDrv
{

class MOpenGLLinkedShaderProgram;

bool operator==(IN const MOpenGLCachedShaderKey& Lhs, IN const MOpenGLCachedShaderKey& Rhs)
{
  return (Lhs.m_shaderType == Rhs.m_shaderType)     &&
         (Lhs.m_glslCodeSize == Rhs.m_glslCodeSize) &&
         (Lhs.m_glslCodeHash == Rhs.m_glslCodeHash);
}

bool operator!=(IN const MOpenGLCachedShaderKey& Lhs, IN const MOpenGLCachedShaderKey& Rhs)
{
  return !(Lhs == Rhs);
}

bool operator==(const MOpenGLCachedLinkedShaderProgramKey& Lhs, const MOpenGLCachedLinkedShaderProgramKey& Rhs)
{
  for (uint64 i = 0; i < MEngine::RHI::MAX_STAGE_NUM; ++i)
  {
    if (Lhs.ShaderHashes[i] != Rhs.ShaderHashes[i])
    {
      return false;
    }
  }

  return true;
}

bool operator!=(const MOpenGLCachedLinkedShaderProgramKey& Lhs, const MOpenGLCachedLinkedShaderProgramKey& Rhs)
{
  return !(Lhs == Rhs);
}

struct MOpenGLCachedShaderKeyHash
{
  using is_transparent = void;
  size_t operator()(IN const MOpenGLCachedShaderKey& InKey) const
  {
    return std::hash<GLenum>{}(InKey.m_shaderType) ^ std::hash<uint64>{}(InKey.m_glslCodeSize) ^ std::hash<uint64>{}(InKey.m_glslCodeHash);
  }
};

struct MOpenGLCachedShaderValue
{

  GLuint Resource;

  MOpenGLCachedShaderValue()
    : Resource{0}
    , m_glslCode{}
  { }

  bool HasCode() const
  {
    return !m_glslCode.empty();
  }

  void WriteGLSLShader(const std::vector<ANSICHAR>& InGLSLCode)
  {
    static_assert(sizeof(InGLSLCode[0]) == sizeof(char), "Expecting GLSL code type to be byte");

    m_glslCode.clear();
    m_glslCode = InGLSLCode;
  }

  std::vector<ANSICHAR> GetGLSLShader() const { return m_glslCode; }


private:
  std::vector<ANSICHAR> m_glslCode;

};

typedef std::unordered_map< MEngine::OpenGLDrv::MOpenGLCachedShaderKey, 
                            MEngine::OpenGLDrv::MOpenGLCachedShaderValue, 
                            MEngine::OpenGLDrv::MOpenGLCachedShaderKeyHash> 
           /**Type alias */ OpenGLShaderCache;

typedef OpenGLShaderCache::iterator OpenGLShaderCacheIterator;
typedef OpenGLShaderCache::const_iterator OpenGLShaderCacheConstIterator;

static OpenGLShaderCache& GetOpenGLShaderCache()
{
  static OpenGLShaderCache s_cache{};
  return s_cache;
}

MOpenGLCachedLinkedShaderProgramKey::MOpenGLCachedLinkedShaderProgramKey()
  : ShaderHashes{}
{
  for (uint64 i = 0; i < MEngine::RHI::MAX_STAGE_NUM; ++i)
  {
    ShaderHashes[i] = 0;
  }
}

MOpenGLCachedLinkedShaderProgramKey::MOpenGLCachedLinkedShaderProgramKey(MOpenGLVertexShader* GLVertexShader, MOpenGLPixelShader* GLPixelShader)
  : MOpenGLCachedLinkedShaderProgramKey{}
{
  ShaderHashes[::EnumCast(MEngine::RHI::EShaderStage::Vertex)] = GLVertexShader->GetGLHash();
  ShaderHashes[::EnumCast(MEngine::RHI::EShaderStage::Pixel)] = GLPixelShader->GetGLHash();
}


struct MOpenGLCachedLinkedShaderProgramKeyHash
{
  using is_transparent = void;
  size_t operator()(IN const MOpenGLCachedLinkedShaderProgramKey& InKey) const
  {
    size_t result = InKey.ShaderHashes[0];

    for (uint64 i = 1; i < MEngine::RHI::MAX_STAGE_NUM; ++i)
    {
      result ^= std::hash<uint64>{}(InKey.ShaderHashes[i]);
    }

    return result;
  }
};

typedef std::unordered_map< MEngine::OpenGLDrv::MOpenGLCachedLinkedShaderProgramKey, 
                            MEngine::OpenGLDrv::MOpenGLLinkedShaderProgram*, 
                            MEngine::OpenGLDrv::MOpenGLCachedLinkedShaderProgramKeyHash> 
           /**Type alias */ OpenGLProgramCache;

static OpenGLProgramCache& GetOpenGLProgramCache()
{
  static OpenGLProgramCache s_cache{};
  return s_cache;
}

MOpenGLShader::MOpenGLShader(IN std::span<const uint8> ShaderCode, GLenum ShaderType)
  : m_nativeResource{ShaderType}
  , m_GLSLCodeKey{}
{ 
  // Read ShaderCode as string(std::vector<char>)
  std::vector<ANSICHAR> codeString{};
  AppendGLSLString(codeString, reinterpret_cast<const ANSICHAR*>(ShaderCode.data()));
  uint64 codeHash = MEngine::Core::FNV1a64(codeString.data(), codeString.size());

  m_GLSLCodeKey = MEngine::OpenGLDrv::MOpenGLCachedShaderKey{ShaderType, codeString.size(), codeHash};

  // TODO Add mutex lock
  {
    MOpenGLCachedShaderValue& foundValue = GetOpenGLShaderCache()[m_GLSLCodeKey];
    m_nativeResource.Resource = foundValue.Resource;

    // Write GLSL code to cache if cached value is not initialized
    if (foundValue.Resource == 0 && !foundValue.HasCode())
    {
      // TODO Some device may not has compatibility to some feature.
      // TODO To make sure that GLSL code can run on all device, we should add some platform-based code.
      // NOTE:GLSLToPlatform
      foundValue.WriteGLSLShader(codeString);
    }
  }
}

void MOpenGLShader::Compile()
{
  OPENGL_STATE_CHECK();

  MOpenGLCachedShaderValue& foundValue = GetOpenGLShaderCache()[m_GLSLCodeKey];
  GLuint& resourceRef = m_nativeResource.Resource;
  const GLenum& typeRef = m_nativeResource.Type;
  resourceRef = foundValue.Resource;

  // Create new shader resource
  if (resourceRef == 0)
  {
    resourceRef = ::glCreateShader(typeRef);
    std::vector<ANSICHAR> GLSLCode = foundValue.GetGLSLShader();
    const ANSICHAR* GLSLCodeData = GLSLCode.data();
    // Assume there is a null terminator or '\n' in GLSL code
    const GLint codeLength = static_cast<GLint>(GLSLCode.size() - 1);
    ::glShaderSource(resourceRef, 1, static_cast<const GLchar**>(&GLSLCodeData), &codeLength);
    ::glCompileShader(resourceRef);

    const bool bSuccess = VerifyShaderCompilationStatus(resourceRef);
    me_assert(bSuccess);

    foundValue.Resource = resourceRef;
  }
}

class MOpenGLLinkedShaderProgram final
{
  public:
    MOpenGLLinkedShaderProgram(IN MOpenGLVertexShader* VertexShader, IN MOpenGLPixelShader* PixelShader)
      : m_programKey{VertexShader, PixelShader}
      , m_programResource{0}
    {
      OPENGL_STATE_CHECK();
      me_assert(VertexShader != nullptr);
      me_assert(PixelShader != nullptr);

      VertexShader->Compile();
      PixelShader->Compile();

      m_programResource = ::glCreateProgram();

      me_assert(VertexShader->GLResource() != 0);
      // Vertex shader
      ::glAttachShader(m_programResource, VertexShader->GLResource());
      
      me_assert(PixelShader->GLResource() != 0);
      // Pixel shader
      ::glAttachShader(m_programResource, PixelShader->GLResource());

      // Link
      ::glLinkProgram(m_programResource);

      const bool bSuccess = VerifyProgramLinkStatus(m_programResource);
      me_assert(bSuccess);

      // Active shader program
      ::glUseProgram(m_programResource);

      GetOpenGLProgramCache()[m_programKey] = this;
    }

  GLuint GLProgramResource() const { return m_programResource; } 

  private:
    const MOpenGLCachedLinkedShaderProgramKey m_programKey;
    GLuint m_programResource;
};

void MOpenGLRHIBackend::SetShaderState(
  IN MOpenGLVertexShader* VertexShader,
  IN MOpenGLPixelShader*  PixelShader,
  IN MOpenGLVertexInputLayout* InputLayout
)
{
  OPENGL_STATE_CHECK();

  // NOTE: We should not delete here
  if (m_drawState.LinkedProgram != nullptr)
  {
    delete m_drawState.LinkedProgram;
    m_drawState.LinkedProgram = nullptr;
  }

  m_drawState.LinkedProgram = new MOpenGLLinkedShaderProgram(VertexShader, PixelShader);
  m_drawState.InputLayout = InputLayout;
}

void MOpenGLRHIBackend::BindShaderState()
{
  OPENGL_STATE_CHECK();

  const MOpenGLLinkedShaderProgram* const linkedProgram = m_drawState.LinkedProgram;
  if (linkedProgram != nullptr)
  {
    ::glUseProgram(linkedProgram->GLProgramResource());
  }
}


} // namespace MEngine::OpenGLDrv

} // namespace MEngine

namespace
{

void AppendGLSLString(OUT std::vector<ANSICHAR>& Dest, IN const ANSICHAR* const Src)
{
  me_assert(Src != nullptr);

  const SIZE_T srcLength = MPlatformStringUtility::Strlen(Src);
  for (SIZE_T i = 0; i < srcLength; ++i)
  {
    Dest.push_back(Src[i]);
  }
}

bool VerifyShaderCompilationStatus(IN GLuint ShaderResource)
{
  OPENGL_STATE_CHECK();

  GLint success{GL_FALSE};
  ::glGetShaderiv(ShaderResource, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE)
  {
    LogShaderCompileFailure(ShaderResource);
    return false;
  }

  return true;
}

bool VerifyProgramLinkStatus(IN GLuint ProgramResource)
{
  OPENGL_STATE_CHECK();

  GLint success{GL_FALSE};
  ::glGetProgramiv(ProgramResource, GL_LINK_STATUS, &success);
  if (success != GL_TRUE)
  {
    LogProgramLinkFailure(ProgramResource);
    return false;
  }

  return true;
}

void LogShaderCompileFailure(IN GLuint ShaderResource)
{
  OPENGL_STATE_CHECK();

  bool bLogFailure = true;
  if (bLogFailure)
  {
    // Use this if logLength is small
    constexpr uint32 STACK_LOG_BUFFER_SIZE = 4096;
    ANSICHAR stackLogBuffer[STACK_LOG_BUFFER_SIZE] = "No log";

    GLint logLength{0};
    ANSICHAR* log = stackLogBuffer;
    bool bLogUseHeap = false;
    ::glGetShaderiv(ShaderResource, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
      if (logLength > STACK_LOG_BUFFER_SIZE)
      {
        // TODO do not use malloc here
        log = static_cast<ANSICHAR*>(::malloc(logLength));
        bLogUseHeap = true;
      }
      else
      {
        // Use stack to read log
        logLength = STACK_LOG_BUFFER_SIZE;
      }
      
      ::glGetShaderInfoLog(ShaderResource, logLength, nullptr, log);
    }

    // TODO do not use cout here
    std::cout << "OpenGL Error: Failed to compile GLSL Shader. Compile log:\n" << log << std::endl;

    if (bLogUseHeap)
    {
      // TODO do note use free here
      ::free(log);
    }
  }
}

void LogProgramLinkFailure(IN GLuint ProgramResource)
{
OPENGL_STATE_CHECK();

  bool bLogFailure = true;
  if (bLogFailure)
  {
    // Use this if logLength is small
    constexpr uint32 STACK_LOG_BUFFER_SIZE = 4096;
    ANSICHAR stackLogBuffer[STACK_LOG_BUFFER_SIZE] = "No log";

    GLint logLength{0};
    ANSICHAR* log = stackLogBuffer;
    bool bLogUseHeap = false;
    ::glGetProgramiv(ProgramResource, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 1)
    {
      if (logLength > STACK_LOG_BUFFER_SIZE)
      {
        // TODO do not use malloc here
        log = static_cast<ANSICHAR*>(::malloc(logLength));
        bLogUseHeap = true;
      }
      else
      {
        // Use stack to read log
        logLength = STACK_LOG_BUFFER_SIZE;
      }
      
      ::glGetProgramInfoLog(ProgramResource, logLength, nullptr, log);
    }

    // TODO do not use cout here
    std::cout << "OpenGL Error: Failed to link program. Log:\n" << log << std::endl;

    if (bLogUseHeap)
    {
      // TODO do note use free here
      ::free(log);
    }
  }
}

}// nameless namespace

// Delete all cached shader
// @see OpenGLDriverRHI.cpp
void DeleteAllShaderResources()
{
  OPENGL_STATE_CHECK();

  {
    MEngine::OpenGLDrv::OpenGLShaderCache& cachedShaders = MEngine::OpenGLDrv::GetOpenGLShaderCache();
    
    for(const auto& [key , value] : cachedShaders)
    {
      ::glDeleteShader(value.Resource);
    }
    cachedShaders.clear();
  }
}