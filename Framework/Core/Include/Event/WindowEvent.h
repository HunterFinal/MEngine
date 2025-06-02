#pragma once

#ifndef _ME_WINDOW_EVENT_
#define _ME_WINDOW_EVENT_

#include "Event/IEventInterface.h"
#include <memory>

namespace MEngine
{
  namespace Core
  {
    class MWindowEvent : public IEventInterface
    {
      public:
        MWindowEvent();
        virtual ~MWindowEvent();

        MWindowEvent(const MWindowEvent& Other);
        MWindowEvent& operator=(const MWindowEvent& Other);
        MWindowEvent(MWindowEvent&& Other) noexcept;
        MWindowEvent& operator=(MWindowEvent&& Other) noexcept;

      private:
        struct Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
  } 
}

#endif // _ME_WINDOW_EVENT_