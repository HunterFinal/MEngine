#pragma once

#ifndef _ME_CORE_SERIALIZATIONCONCEPTS_
#define _ME_CORE_SERIALIZATIONCONCEPTS_

#include "CoreDefines.h"

#if CAN_USE_CONCEPT

#include <type_traits>
#include <concepts>
#include <string>

namespace MEngine
{

namespace Core
{
  template<typename T>
  concept SerializerBase = requires (const T ct, T t, void* Data, int64 Length)
  {
    { t.Serialize(Data, Length) } -> std::same_as<void>;

    { ct.IsValid() } -> std::same_as<bool>;
    { ct.IsLoading() } -> std::same_as<bool>;
  };

  template<typename T>
  concept SerializerWritableState = requires (const T ct)
  {
    { ct.IsSaving() } -> std::same_as<bool>;
  };

  template<typename T>
  concept SerializerErrorAware = requires (const T ct)
  {
    { ct.IsError() } -> std::same_as<bool>;
    { ct.GetError() } -> std::convertible_to<std::string_view>;
  };

  template<typename T>
  concept SerializerSeekable = requires (T t, int64 pos)
  {
    { t.Tell() } -> std::same_as<int64>;
    { t.Seek(pos) } -> std::same_as<void>;
    { t.SeekFromEnd(pos) } -> std::same_as<void>;
  };

  template<typename T>
  concept SerializerResourceManagableBase = requires (const T ct, T t)
  {
    { t.Close() } -> std::same_as<bool>; 

    { ct.IsOpen() } -> std::same_as<bool>;
  };

  template<typename T>
  concept SerializerResourceManagableManually = requires (T t)
  {
    { t.Open() } -> std::same_as<bool>;
  };

  template<typename T>
  concept SerializerHasState = requires (const T ct)
  {
    { ct.Size() } -> std::same_as<int64>;
  };

  template<typename T>
  concept ReadFileSerializer =
    SerializerBase<T> &&
    SerializerErrorAware<T> &&
    SerializerResourceManagableBase<T> &&
    SerializerHasState<T>;

  template<typename T>
  concept FileHandlerBase = requires (const T ct, T t)
  {
    { t.Close() } -> std::same_as<bool>;

    { ct.IsValid() } -> std::same_as<bool>;
    { ct.IsOpen() } -> std::same_as<bool>;
  };

  template<typename T>
  concept DataReadable = requires (T t, uint8* Data, int64 Length)
  {
    { t.Read(Data, Length) } -> std::same_as<bool>;
  };

  template<typename T>
  concept ReadonlyFileHandler =
    FileHandlerBase<T> &&
    DataReadable<T>;

} // namespace MEngine::Core

} // namespace MEngine

#endif // CAN_USE_CONCEPT

#endif // _ME_CORE_SERIALIZATIONCONCEPTS_
