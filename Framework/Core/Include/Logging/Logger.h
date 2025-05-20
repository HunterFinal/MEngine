// MEngine Logger

#pragma once

#ifndef ME_CORE_LOGGER
#define ME_CORE_LOGGER

#include "Misc/CoreDefines.h"

template<typename LoggerType, typename... Args>
concept TemplateLogger = requires(LoggerType LoggerEntity, Args... args)
{
  LoggerEntity.Startup();
  LoggerEntity.LogTrace(std::forward<Args>(args)...);
  LoggerEntity.LogInfo(std::forward<Args>(args)...);
  LoggerEntity.LogWarn(std::forward<Args>(args)...);
  LoggerEntity.LogError(std::forward<Args>(args)...);
  LoggerEntity.LogFatal(std::forward<Args>(args)...);
  LoggerEntity.Terminate();
};

namespace MEngine
{
  namespace Core
  {
    struct CORE_API Logger
    {
      private:
        enum Type : uint8
        {
          Trace = 0,
          Info,
          Warning,
          Error,
          Fatal,
        };

        struct LoggerConcept_Internal
        {
            virtual ~LoggerConcept_Internal() = default;

            template<typename... ArgTypes>
            void Log(const Type LogLevel, ArgTypes&&... Args)
            {
              if constexpr (LogLevel == Trace)
              {
                LogTrace_Impl(std::forward<ArgTypes>(Args)...);
              }
              else if constexpr (LogLevel == Info)
              {
                LogInfo_Impl(std::forward<ArgTypes>(Args)...);
              }
              else if constexpr (LogLevel == Warning)
              {
                LogWarn_Impl(std::forward<ArgTypes>(Args)...);
              }
              else if constexpr (LogLevel == Error)
              {
                LogError_Impl(std::forward<ArgTypes>(Args)...);
              }
              else if constexpr (LogLevel == Fatal)
              {
                LogFatal_Impl(std::forward<ArgTypes>(Args)...);
              }
            }

          protected:
            template<typename... ArgTypes>
            void LogTrace_Impl(ArgTypes&&... Args)
            { }
            template<typename... ArgTypes>
            void LogInfo_Impl(ArgTypes&&... Args)
            { }
            template<typename... ArgTypes>
            void LogWarn_Impl(ArgTypes&&... Args)
            { }
            template<typename... ArgTypes>
            void LogError_Impl(ArgTypes&&... Args)
            { }
            template<typename... ArgTypes>
            void LogFatal_Impl(ArgTypes&&... Args)
            { }

          public:
            void LogTrace(std::tuple)
        };
        
        // TODO
        template<TemplateLogger LoggerEntity>
        struct LoggerModel_Internal : public LoggerConcept_Internal
        {
          LoggerModel_Internal(LoggerEntity&& Entity)
            : m_entity(std::move(Entity))
          { }

          private:
            LoggerEntity m_entity;
        };
        
      public:
      Logger() = default;
      virtual ~Logger() = default;
      
      /**
       * Not copyable and not moveable
       */
      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;
      Logger(Logger&&) noexcept = delete;
      Logger& operator=(Logger&&) noexcept = delete;

      virtual void Startup() = 0;
      virtual void Terminate() = 0;

      /**
       * Logging message methods
       */
      template<typename... ArgTypes>
      void LogTrace(ArgTypes&&... args) { m->Log(Trace, std::forward<ArgTypes>(args)...); }
      
      template<typename... ArgTypes>
      void LogInfo(ArgTypes&&... args) { m->Log(Info, std::forward<ArgTypes>(args)...); }

      template<typename... ArgTypes>
      void LogWarning(ArgTypes&&... args) { m->Log(Warning, std::forward<ArgTypes>(args)...); }

      template<typename... ArgTypes>
      void LogError(ArgTypes&&... args) { m->Log(Error, std::forward<ArgTypes>(args)...); }

      template<typename... ArgTypes>
      void LogFatal(ArgTypes&&... args) { m->Log(Fatal, std::forward<ArgTypes>(args)...); }

      private:
        std::unique_ptr<LoggerConcept_Internal> m;
    }; 
  }
}

#endif // ME_CORE_LOGGER