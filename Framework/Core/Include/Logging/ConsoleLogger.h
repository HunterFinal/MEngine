#pragma once

#ifndef ME_CORE_CONSOLE_LOGGER
#define ME_CORE_CONSOLE_LOGGER

#include "IOutputInterface.h"
#include <memory>

namespace MEngine
{
  namespace Core
  {
    struct CORE_API ConsoleLogger : public IOutputInterface
    {
      public:
        ConsoleLogger();
        virtual ~ConsoleLogger();

        /**Start of IOutputInterface interface */
        #pragma region IOutputInterface interface
          virtual void Startup() override;
          virtual void Terminate() override;
          virtual void Serialize(IN const ANSICHAR* Data) override;
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