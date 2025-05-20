#include "Logging/SystemLogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MEngine
{
  namespace Core
  {
    struct SystemLogger::Impl
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
          }

          m_bIsStartingup = true;
        }

        void Terminate_Impl()
        {
          m_logger.reset();
          m_bIsStartingup = false;
        }

      private:
        std::shared_ptr<LoggerEntity> m_logger;
        uint8 m_bIsStartingup : 1;

    };

    SystemLogger::SystemLogger()
      : m_pImpl(std::make_unique<Impl>())
    { }

    SystemLogger::~SystemLogger()
    {
      m_pImpl.release();
    }

    void SystemLogger::Startup() { m_pImpl->Startup_Impl(); }
    void SystemLogger::Terminate() { m_pImpl->Terminate_Impl(); }
  }
}