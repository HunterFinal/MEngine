#pragma once

#ifndef _ME_CORE_SERIALIZATION_FILESERIALIZER_
#define _ME_CORE_SERIALIZATION_FILESERIALIZER_

#include "Serialization/Serializer.h"
#include "Serialization/SerializationConcepts.h"

#include <string>
#include <memory>
#include <vector>

namespace MEngine
{

namespace Core
{
  class MFileReadSerializer : private MSerializerErrorState
  {
    public:
      using MSerializerErrorState::GetError;
      using MSerializerErrorState::IsError;

    private:
      TYPEDEF(std::wstring, MString);

      struct Concept
      {
        virtual ~Concept() = default;

        virtual bool Read(uint8* Data, int64 Length) = 0;
        virtual bool Close() = 0;
        virtual bool IsValid() const = 0;
        virtual bool IsOpen() const = 0;
      };

      template<MEngine::Core::ReadonlyFileHandler FileHandler>
      struct Model : public Concept
      {
        Model(IN FileHandler* Handler)
          : m_handler{Handler}
        { }

        bool Read(uint8* Data, int64 Length) override
        {
          return m_handler->Read(Data, Length);
        }

        bool Close() override
        {
          return m_handler->Close();
        }

        bool IsValid() const override
        {
          return m_handler->IsValid();
        }

        bool IsOpen() const override
        {
          return m_handler->IsOpen();
        }

        private:
          std::unique_ptr<FileHandler> m_handler;
      };

    public:
      template<MEngine::Core::ReadonlyFileHandler FileHandler>
      CORE_API MFileReadSerializer(IN FileHandler* Handler, IN const TCHAR* Filename, IN int64 FileSize, IN SIZE_T BufferSize);

      CORE_API ~MFileReadSerializer();

      CORE_API void Serialize(void* Data, int64 Length);
      CORE_API bool IsValid() const;
      CORE_API bool IsLoading() const;

      CORE_API bool Close();
      CORE_API bool IsOpen() const;

      FORCEINLINE int64 Size() const { return m_size; }

      /**Start MSerializerErrorState interface */
      CORE_API virtual std::string GetName() const override;
      /**End MSerializerErrorState interface */

    private:
      bool CacheFileBuffer(IN int64 CacheStartPos);

    private:
      std::unique_ptr<Concept> m_pImpl;

      MString m_filename;
      int64 m_pos;
      int64 m_size;

      // Cache buffer
      int64 m_bufferPos;
      SIZE_T m_bufferSize;
      std::vector<uint8> m_bufferArray;

      uint8 m_bIsLoading : 1;

  };

  template<MEngine::Core::ReadonlyFileHandler FileHandler>
  MFileReadSerializer::MFileReadSerializer(IN FileHandler* Handler, IN const TCHAR* Filename, IN int64 FileSize, IN SIZE_T BufferSize)
    : m_pImpl{std::make_unique< Model < FileHandler > >(Handler)}
    , m_filename{Filename}
    , m_pos{0}
    , m_size{FileSize}
    , m_bufferPos{0}
    , m_bufferSize{BufferSize}
    , m_bufferArray{}
    , m_bIsLoading{true}
  {
    me_assert(Handler != nullptr);

    // Reset error state
    this->Reset();
  }

}

}


#endif // _ME_CORE_SERIALIZATION_FILESERIALIZER_