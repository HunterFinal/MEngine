#pragma once

#ifndef ME_CORE_SYS_LOGGER
#define ME_CORE_SYS_LOGGER

#include "Logger.h"
#include <memory>

namespace MEngine
{
  namespace Core
  {
    struct CORE_API SystemLogger : public Logger
    {
      public:
        SystemLogger();
        virtual ~SystemLogger();

        /**Start of Logger interface */
        #pragma region Logger interface
          virtual void Startup() override;
          virtual void Terminate() override;
        #pragma endregion Logger interface
        /**End of Logger interface */

      private:
       /**Implementation strategy */
        struct Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
  }
}

#endif // ME_CORE_SYS_LOGGER