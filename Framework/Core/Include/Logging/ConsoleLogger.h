#pragma once

#ifndef ME_CORE_CONSOLE_LOGGER
#define ME_CORE_CONSOLE_LOGGER

#include "IOutputInterface.h"
#include <memory>

namespace MEngine
{
  namespace Core
  {
    struct ConsoleLogger : public IOutputInterface
    {
      public:
        CORE_API ConsoleLogger();
        CORE_API virtual ~ConsoleLogger() = default;

        /**Start of IOutputInterface interface */
        #pragma region IOutputInterface interface
          CORE_API virtual void Startup() override;
          CORE_API virtual void Terminate() override;
          CORE_API virtual void Serialize(IN const ANSICHAR* Data) override;
          CORE_API virtual void Flush() override;
        #pragma endregion IOutputInterface interface
        /**End of IOutputInterface interface */

      private:
       /**Implementation strategy */
        struct Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
  }
}

#endif // ME_CORE_CONSOLE_LOGGER