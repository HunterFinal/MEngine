#pragma once

#ifndef ME_ABSTRACT_DELEGATE
#define ME_ABSTRACT_DELEGATE

#include "Misc/CoreDefines.h"
#include "Delegates/IDelegateInterface.h"

#include <memory>

namespace MEngine
{
  namespace Core
  {
    /**
     * Base of singleCast delegate
     * Non thread-safe
     * Use it without multithreaded programming
     */
    class CORE_API MAbstractDelegate
    {
      /**
       * Default constructor
       */
      protected:
        explicit MAbstractDelegate() = default;

      public:
        virtual ~MAbstractDelegate();

        MAbstractDelegate(IN MAbstractDelegate&& Other) noexcept;
        MAbstractDelegate& operator=(IN MAbstractDelegate&& Other) noexcept;
        MAbstractDelegate(IN const MAbstractDelegate& Other) = delete;
        MAbstractDelegate& operator=(IN const MAbstractDelegate& Other) = delete;

        void Unbind();
        void* GetInstancePtr() const;
        template<typename UserClass>
        FORCEINLINE UserClass* GetTypedInstancePtr() const;
        bool IsBound() const;
        bool IsBoundToInstance(IN const void* InstancePtr) const;
        MDelegateHandle GetHandle() const;

      protected:
        template<typename DelegateInstanceType, typename... InstanceConstrucParams>
        FORCEINLINE void CreateInstance(IN InstanceConstrucParams... Params);

        FORCEINLINE IDelegateInterface* GetDelegateInterfaceInternal()
        {
          return m_delegateInterface.get();
        }

        FORCEINLINE const IDelegateInterface* GetDelegateInterfaceInternal() const
        {
          return m_delegateInterface.get();
        }

      private:
        std::unique_ptr<IDelegateInterface> m_delegateInterface;
    };

    template<typename UserClass>
    UserClass* MAbstractDelegate::GetTypedInstancePtr() const
    {
      return dynamic_cast<UserClass*>(GetInstancePtr());
    }

    template<typename DelegateInstanceType, typename... InstanceConstrucParams>
    void MAbstractDelegate::CreateInstance(IN InstanceConstrucParams... Params)
    {
      if(m_delegateInterface != nullptr)
      {
        m_delegateInterface.reset();
      }

      m_delegateInterface = std::make_unique<DelegateInstanceType>(std::forward<InstanceConstrucParams>(Params)...);
    }


  }
}

#endif // ME_ABSTRACT_DELEGATE