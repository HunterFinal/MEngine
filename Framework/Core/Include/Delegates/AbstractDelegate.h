#pragma once

#ifndef ME_ABSTRACT_DELEGATE
#define ME_ABSTRACT_DELEGATE

namespace MEngine
{
  namespace Core
  {
    class MAbstractDelegate
    {
      /**
       * Default constructor
       */
      protected:
        explicit MAbstractDelegate() = default;

      public:
        virtual ~MAbstractDelegate();

        MAbstractDelegate(MAbstractDelegate&& Other) noexcept;
        MAbstractDelegate& operator=(MAbstractDelegate&& Other) noexcept;

      private:
        
    };
  }
}

#endif // ME_ABSTRACT_DELEGATE