// MEngine ConsoleLogger definition

#include "Logging/ConsoleLogger.h"

// Third party
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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

          // TODO
          // Free another console when use ConsoleLogger!!!!
          FreeConsole();
        }
        ~Impl()
        {
          Terminate_Impl();

          ::memset(this, 0, sizeof(*this));
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

              //bstd::ios::sync_with_stdio();

              std::cout.clear();
              std::wcout.clear();
              std::cerr.clear();
              std::wcerr.clear();
              std::cin.clear();
              std::wcin.clear();
            }

            #if USE_UTF8_CHAR
              _setmode(fileno(stdout), _O_U8TEXT);
              _setmode(fileno(stderr), _O_U8TEXT);
            #else
              _setmode(fileno(stdout), _O_TEXT);
              _setmode(fileno(stderr), _O_TEXT);
            #endif
          }

          m_bIsStartingup = true;
          m_logger = spdlog::stdout_color_mt("SYS_LOGGER");
          if (m_logger != nullptr)
          {
            m_logger->set_level(spdlog::level::trace);
            m_logger->trace("Hello! Var{0}", 100);
            m_logger->warn("FFFFF");
          }
        }

        void Terminate_Impl()
        {
          if (m_bIsStartingup)
          {
            FreeConsole();
            m_logger.reset();
            m_bIsStartingup = false;
          }
        }

        void Serialize_Impl(IN const ANSICHAR* Data)
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
    void ConsoleLogger::Serialize(IN const ANSICHAR* Data) { m_pImpl->Serialize_Impl(Data); }
  }
}