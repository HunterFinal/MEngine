// MEngine ConsoleLogger definition

#include "HAL/PlatformMacroHelper.h"
#include "Logging/ConsoleLogger.h"

// Third party
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// standard
#include <cstring>
#include <fcntl.h>
#include <format>
#include <io.h>
#include <iostream>
#include <windows.h>

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
          Terminate_Impl();
        }

        void Startup_Impl()
        {
          if (m_bIsStartingup)
          {
            return;
          }

          // Free console if it exists
          if (GetConsoleWindow() != nullptr)
          {
            FreeConsole();
          }

          // Create new console
          if (!AllocConsole())
          {
            return;
          }

          // Set stdout target
          {
            // Redirection stdout,stderr,stdin
            {
              FILE* stream;
  
              _wfreopen_s(&stream, L"CONOUT$", L"w+", stdout);
              _wfreopen_s(&stream, L"CONOUT$", L"w+", stderr);
              _wfreopen_s(&stream, L"CONIN$" , L"r", stdin );

              std::ios::sync_with_stdio(true);

              std::cout.clear();
              std::wcout.clear();
              std::cerr.clear();
              std::wcerr.clear();
              std::cin.clear();
              std::wcin.clear();

            }

            #if USE_UTF8_CHAR
              _setmode(POSIX_FIX(fileno(stdout)), _O_U8TEXT);
              _setmode(POSIX_FIX(fileno(stderr)), _O_U8TEXT);
            #else
              _setmode(POSIX_FIX(fileno(stdout)), _O_TEXT);
              _setmode(POSIX_FIX(fileno(stderr)), _O_TEXT);
            #endif
          }

          // Initialize spdlog
          m_logger = spdlog::get("SYS_LOGGER");
          if (m_logger == nullptr)
          {
            // spdlog::logger initialization
            auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            m_logger = std::make_shared<spdlog::logger>("SYS_LOGGER", sink);
            spdlog::register_logger(m_logger);

            if (m_logger != nullptr)
            {
              m_logger->set_level(spdlog::level::trace);
              m_logger->flush_on(spdlog::level::trace);
              spdlog::flush_every(std::chrono::seconds(1));
              m_logger->info("Console Logger Initialized");
              m_logger->flush();

              m_bIsStartingup = true;
            }

          }
        }

        void Terminate_Impl()
        {
          if (m_bIsStartingup)
          {
            spdlog::shutdown();

            FreeConsole();
            m_logger.reset();
            m_bIsStartingup = false;
          }
        }

        void Serialize_Impl(IN const ANSICHAR* Data)
        {
          if (m_bIsStartingup)
          {
            std::string str{Data};
            m_logger->debug(str);
          }
        }

        void Flush_Impl()
        {
          if (m_bIsStartingup)
          {
            m_logger->flush();
          }
        }

      private:
        std::shared_ptr<LoggerEntity> m_logger;
        uint8 m_bIsStartingup : 1;

    };

    ConsoleLogger::ConsoleLogger()
      : m_pImpl(std::make_unique<Impl>())
    { }

    void ConsoleLogger::Startup()                           { m_pImpl->Startup_Impl();        }
    void ConsoleLogger::Terminate()                         { m_pImpl->Terminate_Impl();      }
    void ConsoleLogger::Serialize(IN const ANSICHAR* Data)  { m_pImpl->Serialize_Impl(Data);  } 
    void ConsoleLogger::Flush()                             { m_pImpl->Flush_Impl();          }
  }
}
