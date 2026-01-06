#pragma once

#ifndef _ME_CORE_SERIALIZATION_SERIALIZER_
#define _ME_CORE_SERIALIZATION_SERIALIZER_

#include "CoreDefines.h"
#include <string>

namespace MEngine
{

namespace Core
{
  class MSerializerErrorState
  {
    public:
      CORE_API MSerializerErrorState();
      CORE_API MSerializerErrorState(const MSerializerErrorState& Other);
      CORE_API MSerializerErrorState& operator=(const MSerializerErrorState& Other);

      CORE_API virtual ~MSerializerErrorState() = 0;

      // TODO YAGNI
      // CORE_API virtual MSerializerErrorState& GetRootState() &;
      // CORE_API const MSerializerErrorState& GetRootState() const&;

      FORCEINLINE std::string_view GetError() const { return m_errorMsg; }
      FORCEINLINE bool IsError() const { return m_bIsError; }
      FORCEINLINE virtual std::string GetName() const { return std::string{}; };
      
      CORE_API void SetError(IN const std::string& ErrorMsg);
      CORE_API void Reset();

    private:
      std::string m_errorMsg;

      uint8 m_bIsError : 1;
  };
  
} // namespace MEngine::Core

} // namespace MEngine

#endif // _ME_CORE_SERIALIZATION_SERIALIZER_