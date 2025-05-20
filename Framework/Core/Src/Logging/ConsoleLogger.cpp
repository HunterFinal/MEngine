#include "Logging/ConsoleLogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <format>
#include <cstring>

namespace MEngine
{
  namespace Core
  {
    struct ConsoleLogger::Impl
    {
      private:
        TYPEDEF(spdlog::logger, LoggerEntity);
      public:
        Impl()
          : m_logger{nullptr}
          , m_bIsStartingup{false}
        { 
          // TODO
          spdlog::set_pattern("%^[%T] %n: %v%$");
        }
        ~Impl()
        {
          if (m_bIsStartingup)
          {
            m_logger.reset();
            m_bIsStartingup = false;
          }

          ::memset(this, 0, sizeof(*this));
        }

        void Startup_Impl()
        {
          if (m_bIsStartingup)
          {
            return;
          }

          m_logger = spdlog::stdout_color_mt("SYS_LOGGER");
          if (m_logger != nullptr)
          {
            m_logger->set_level(spdlog::level::trace);
            m_logger->trace("Hello! Var{0}", 100);
            m_logger->warn("FFFFF");
          }

          m_bIsStartingup = true;
        }

        void Terminate_Impl()
        {
          m_logger.reset();
          m_bIsStartingup = false;
        }

        void Serialize_Impl(const ANSICHAR* Data)
        {
          std::string str{Data};
          m_logger->info(str);
        }

      private:
        std::shared_ptr<LoggerEntity> m_logger;
        uint8 m_bIsStartingup : 1;

    };

    ConsoleLogger::ConsoleLogger()
      : m_pImpl(std::make_unique<Impl>())
    { }

    ConsoleLogger::~ConsoleLogger()
    {
      m_pImpl.release();
    }

    void ConsoleLogger::Startup() { m_pImpl->Startup_Impl(); }
    void ConsoleLogger::Terminate() { m_pImpl->Terminate_Impl(); }
    void ConsoleLogger::Serialize(const ANSICHAR* Data) { m_pImpl->Serialize_Impl(Data); }
  }
}