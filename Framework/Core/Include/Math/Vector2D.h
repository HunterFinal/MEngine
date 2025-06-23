// MEngine vector2D definitions
#pragma once

#ifndef MENGINE_MATH_VECTOR2D
#define MENGINE_MATH_VECTOR2D

#include "Math/MathForward.h"
#include "Math/Axis.h"
#include "Math/MEngineMathUtility.h"
#include "Macro/AssertionMacros.h"
#include "Macro/ClassMacroHelpers.h"
#include "Templates/METypeTraits.h"

#include <type_traits>

#ifdef _MSC_VER
#pragma warning (push)
// テンプレート関数がグローバル変数に対してShadowing　warningsを生成することを防ぐ
// Ensure template functions don't generate shadowing warnings against global variables at the point of instantiation
#pragma warning (disable : 4459)
// MSVCの仕様により、無名テンプレート引数 + デフォルト値が無視される警告メッセージ生成を防ぐ
// Ensure Nameless template variable with default value don't generate warnings in MSVC
#pragma warning (disable : 4544)
// MSVCの仕様により、無名共用体と無名構造体に対する警告メッセージを無視
#pragma warning (disable : 4201)
#endif

// MEngine namespace
namespace MEngine
{
  // MEngine::Math namespace
  namespace Math
  {
    template<typename FloatingType>
    struct MVector2D
    {
      static_assert(std::is_floating_point_v<FloatingType>, "Vector2D type must be floating point");
      
      public:
        TYPEDEF(FloatingType, Type);
        GENERATE_CLASS_DEF(MVector2D<Type>);
        
      union
      {
        struct
        {
          // Vector's X component;
          Type X;

          // Vector's Y component;
          Type Y;

        };

        // internal use
        Type XY[2];
      };

      // zero vector (0, 0)
      CORE_API static const MVector2D<Type> ZeroVector;

      // one vector (1, 1)
      CORE_API static const MVector2D<Type> OneVector;

      // MEngine right vector (1, 0)
      CORE_API static const MVector2D<Type> RightVector;

      // MEngine left vector (-1, 0)
      CORE_API static const MVector2D<Type> LeftVector;

      // MEngine up vector (0, 1)
      CORE_API static const MVector2D<Type> UpVector;

      // MEngine down vector (0, -1)
      CORE_API static const MVector2D<Type> DownVector;

      // Unit X axis vector (1, 0)
      CORE_API static const MVector2D<Type> XAxisVector;

      // Unit Y axis vector (0, 1)
      CORE_API static const MVector2D<Type> YAxisVector;

      // -----------------
      // static method
      // -----------------
      static FORCEINLINE MVector2D<Type> Zero() 
      {
        return ZeroVector;
      } 

      static FORCEINLINE MVector2D<Type> One()
      {
        return OneVector;
      }

      static FORCEINLINE MVector2D<Type> Right()
      {
        return RightVector;
      }

      static FORCEINLINE MVector2D<Type> Left()
      {
        return LeftVector;
      }

      static FORCEINLINE MVector2D<Type> Up()
      {
        return UpVector;
      }

      static FORCEINLINE MVector2D<Type> Down()
      {
        return DownVector;
      }

      static FORCEINLINE MVector2D<Type> UnitX()
      {
        return XAxisVector;
      }

      static FORCEINLINE MVector2D<Type> UnitY()
      {
        return YAxisVector;
      }

      // ---------------
      // Constructors
      // ---------------

      // default Constructors
      FORCEINLINE MVector2D();

      /** 
       * using initial values for each component
       *
       * @param InX X coord
       * @param InY Y coord
       */
      FORCEINLINE MVector2D(IN Type InX, IN Type InY);

      /**
       * Convert different type vector to this type
       */
      template<typename DiffType, TEMPLATE_CONDITION_DECLARATION(!std::is_same_v<Type, DiffType>)>
      explicit MVector2D(const MVector2D<DiffType>& Other);

      // end of Constructors

      /**
       * Calculate dot product
       * 
       * @param OtherV The other vector
       * @return The dot product
       */
      FORCEINLINE Type Dot(const ThisClass& OtherV) const;

      /**
       * Calculate dot product of two vectors
       * 
       * @param V1 The first vector
       * @param V2 The second vector
       * @return The dot product
       */
       FORCEINLINE static Type DotProduct(const ThisClass& V1, const ThisClass& V2);

      private:
        /**
         * INNER FUNCTION
         * Calculate dot product
         * 
         * @param OtherV The other vector
         * @return The dot product
         */
        FORCEINLINE Type DotInner(const ThisClass& OtherV) const;

      public:

        /**
         * Check against another vector for equality
         * 
         * @param OtherV The other vector to check
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE bool Equals(const ThisClass& OtherV, Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        static FORCEINLINE bool Equals(const ThisClass& V1, const ThisClass& V2, Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL);

        /**
         * Check vector is zero vector
         * 
         * @return true if all components are exactly zero, false otherwise
         */
        FORCEINLINE bool IsZero() const;

        /**
         * Check all components of the vector is nearly zero within tolerance
         * 
         * @param Tolerance Error Tolerance
         * @return true if the vector is near to zero, false otherwise
         */
        FORCEINLINE bool IsNearlyZero(Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Get the magnitude of this vector
         * 
         * @return The magnitude of this vector
         */
        FORCEINLINE Type Magnitude() const;

        /**
         * Get the squared magnitude of this vector
         * 
         * @return The squared magnitude of this vector
         */
        FORCEINLINE Type SquaredMagnitude() const;

        /**
         * Check if this vector is normalized
         * 
         * @return true if normalized, false otherwise
         */
        FORCEINLINE bool IsNormalized() const;

        /**
         * Normalize this vector if it's magnitude is larger than a tolerance, leaves it unchange if not
         * 
         * @param Tolerance Error Tolerance
         * @return true if normalize successfully, false otherwise
         */
        FORCEINLINE bool Normalize(Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL);
        
        /**
         * Gets normalized version of this vector if it's magnitude is larger than a tolerance, return ZeroVector if not
         * 
         * @param Tolerance Error Tolerance
         * @return A normalized copy of this vector if success, ZeroVector otherwise
         */
        FORCEINLINE MVector2D<Type> GetNormalizedCopy(Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

      public:

        // ---------------------------------------
        // operator overloads
        // ---------------------------------------
        /**
         * Gets the result of component-wise addition of two vectors
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector addition
         */
        friend FORCEINLINE MVector2D<Type> operator+(const MVector2D<Type>& V1, const MVector2D<Type>& V2);

        /**
         * Gets the result of component-wise subtraction of two vectors
         *
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector subtraction
         */
        friend FORCEINLINE MVector2D<Type> operator-(const MVector2D<Type>& V1, const MVector2D<Type>& V2);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param LhsV The left-head side vector
         * @param Scale Value to multiply each component
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector2D<Type> operator*(const MVector2D<Type>& LhsV, ScaleType Scale);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param Scale Value to multiply each component
         * @param RhsV The right-head side vector
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector2D<Type> operator*(ScaleType Scale, const MVector2D<Type>& RhsV);

        /**
         * Gets the result of dividing each component by scale
         * 
         * @param V The vector
         * @param Scale Value to divide each component
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector2D<Type> operator/(const MVector2D<Type>& V, ScaleType Scale);

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are equal, false otherwise
         */
        friend FORCEINLINE bool operator==(const MVector2D<Type>& V1, const MVector2D<Type>& V2);

        /**
         * Check two vectors for inequality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are not equal, false otherwise
         */
        friend FORCEINLINE bool operator!=(const MVector2D<Type>& V1, const MVector2D<Type>& V2);

        /**
         * Get a affirmed copy of this vector
         * same as this
         * 
         * @return A affirmed copy of this
         */
        FORCEINLINE MVector2D<Type> operator+() const;

        /**
         * Get a negated copy of this vector
         * 
         * @return A negated copy of this
         */
        FORCEINLINE MVector2D<Type> operator-() const;

        /**
         * Adds another vector to this vector
         * Component-wise addition
         * 
         * @param OtherV Vector to add from this
         * @return This vector after addition
         */
        FORCEINLINE MVector2D<Type>& operator+=(const ThisClass& OtherV);

        /**
         * Subtracts another vector to this vector
         * Component-wise subtraction
         * 
         * @param OtherV Vector to subtract from this
         * @return This vector after subtraction
         */
        FORCEINLINE MVector2D<Type>& operator-=(const ThisClass& OtherV);

        /**
         * Multiply this vector
         * Component-wise multiplication
         * 
         * @param Scale Value to multiply each component
         * @return This vector after Multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector2D<Type>& operator*=(ScaleType Scale);

        /**
         * Divide this vector
         * Component-wise Dividing
         * 
         * @param Scale Value to divide each component
         * @return This vector after Dividing
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector2D<Type>& operator/=(ScaleType Scale);

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return reference to component
         */
        FORCEINLINE Type& operator[](SIZE_T Index) &;

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return const reference to component
         */
        FORCEINLINE const Type& operator[](SIZE_T Index) const&;

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return copy of component
         */
        FORCEINLINE Type operator[](SIZE_T Index) const&&;
    };

    
    template<typename Type>
    FORCEINLINE MVector2D<Type>::MVector2D()
      : X(0)
      , Y(0)
    {}

    template<typename Type>
    FORCEINLINE MVector2D<Type>::MVector2D(IN Type InX, IN Type InY)
      : X(InX)
      , Y(InY)
    {}

    template<typename Type>
    template<typename DiffType, TEMPLATE_CONDITION_DEFINITION(!std::is_same_v<Type, DiffType>)>
    MVector2D<Type>::MVector2D(const MVector2D<DiffType>& Other)
      : MVector2D<Type>((Type)Other.X, (Type)Other.Y)
    {}

    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::Dot(const MVector2D<Type>& OtherV) const
    {
      return DotInner(OtherV);
    }

    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::DotProduct(const MVector2D<Type>& V1, const MVector2D<Type>& V2)
    {
      return V1.DotInner(V2);
    } 

    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::DotInner(const MVector2D<Type>& OtherV) const
    {
      return (X * OtherV.X) + (Y * OtherV.Y);
    }

    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::Equals(const MVector2D<Type>& OtherV, Type Tolerance) const
    {
      return (MMath::Abs(X - OtherV.X) <= Tolerance) && (MMath::Abs(Y - OtherV.Y) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::Equals(const MVector2D<Type>& V1, const MVector2D<Type>& V2, Type Tolerance)
    {
      return (MMath::Abs(V1.X - V2.X) <= Tolerance) && (MMath::Abs(V1.Y - V2.Y) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::IsZero() const
    {
      return (X == 0) && (Y == 0);
    }

    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::IsNearlyZero(Type Tolerance) const
    {
      return (MMath::Abs(X) <= Tolerance) &&
             (MMath::Abs(Y) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::Magnitude() const
    {
      return MMath::Sqrt(SquaredMagnitude());
    }

    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::SquaredMagnitude() const
    {
      return (X * X) + (Y * Y);
    }

    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::IsNormalized() const
    {
      return (MMath::Abs((Type)1 - SquaredMagnitude()) <= MMath::VECTOR_NORMALIZED_THRESHOLD);
    }

    /**
     * Normalize this vector if it's magnitude is larger than a tolerance, leaves it unchange if not
     * 
     * @param Tolerance Error Tolerance
     * @return true if normalize successfully, false otherwise
     */
    template<typename Type>
    FORCEINLINE bool MVector2D<Type>::Normalize(Type Tolerance)
    {
      const Type squaredMag = SquaredMagnitude();
      if (squaredMag <= Tolerance)
      {
        return false;
      } 

      const Type realScale = static_cast<Type>(1) / MMath::Sqrt(squaredMag);

      X *= realScale;
      Y *= realScale;
      return true;
    }
    
    template<typename Type>
    FORCEINLINE MVector2D<Type> MVector2D<Type>::GetNormalizedCopy(Type Tolerance) const
    {
      const Type squaredMag = SquaredMagnitude();
      if (squaredMag <= Tolerance)
      {
        return ZeroVector;
      }

      const Type realScale = static_cast<Type>(1) / MMath::Sqrt(squaredMag);
      return MVector2D<Type>
             {
                (X * realScale),
                (Y * realScale)
             };
    }

    // -------------------------------------------------------
    // MVector<Type> operator overload definitions
    // -------------------------------------------------------

    template<typename Type>
    FORCEINLINE MVector2D<Type> operator+(const MVector2D<Type>& V1, const MVector2D<Type>& V2)
    {
      return MVector2D<Type>
             {
                (V1.X + V2.X),
                (V1.Y + V2.Y)            
             };
    }

    template<typename Type>
    FORCEINLINE MVector2D<Type> operator-(const MVector2D<Type>& V1, const MVector2D<Type>& V2)
    {
      return MVector2D<Type>
             {
                (V1.X - V2.X),
                (V1.Y - V2.Y)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type> operator*(const MVector2D<Type>& LhsV, ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (LhsV.X * realScale),
                (LhsV.Y * realScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type> operator*(ScaleType Scale, const MVector2D<Type>& RhsV)
    {
      const Type realScale = static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (RhsV.X * realScale),
                (RhsV.Y * realScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type> operator/(const MVector2D<Type>& V, ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (V.X * realScale),
                (V.Y * realScale)
             };
    }

    template<typename Type>
    FORCEINLINE bool operator==(const MVector2D<Type>& V1, const MVector2D<Type>& V2)
    {
      return (V1.X == V2.X) && (V1.Y == V2.Y);
    }

    template<typename Type>
    FORCEINLINE bool operator!=(const MVector2D<Type>& V1, const MVector2D<Type>& V2)
    {
      return !(V1 == V2);
    }

    template<typename Type>
    FORCEINLINE MVector2D<Type> MVector2D<Type>::operator+() const
    {
      return MVector2D<Type>{X, Y};
    }

    template<typename Type>
    FORCEINLINE MVector2D<Type> MVector2D<Type>::operator-() const
    {
      return MVector2D<Type>{-X, -Y};
    }

    template<typename Type>
    FORCEINLINE MVector2D<Type>& MVector2D<Type>::operator+=(const ThisClass& OtherV)
    {
      X += OtherV.X;
      Y += OtherV.Y;

      return *this;
    }

    /**
     * Subtracts another vector to this vector
     * Component-wise subtraction
     * 
     * @param OtherV Vector to subtract from this
     * @return This vector after subtraction
     */
    template<typename Type>
    FORCEINLINE MVector2D<Type>& MVector2D<Type>::operator-=(const ThisClass& OtherV)
    {
      X -= OtherV.X;
      Y -= OtherV.Y;

      return *this;
    }
    
    /**
     * Multiply this vector
     * Component-wise multiplication
     * 
     * @param Scale Value to multiply each component
     * @return This vector after Multiplication
     */
    template<typename Type>
    template<typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type>& MVector2D<Type>::operator*=(ScaleType Scale)
    {
      X *= Scale;
      Y *= Scale;

      return *this;
    }

    /**
     * Divide this vector
     * Component-wise Dividing
     * 
     * @param Scale Value to divide each component
     * @return This vector after Dividing
     */
    template<typename Type>
    template<typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type>& MVector2D<Type>::operator/=(ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      
      X *= realScale;
      Y *= realScale;

      return *this;
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return reference to component
     */
    template<typename Type>
    FORCEINLINE Type& MVector2D<Type>::operator[](SIZE_T Index) &
    {
      me_assert((Index >= 0) && (Index < 2));

      return XY[Index];
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return const reference to component
     */
    template<typename Type>
    FORCEINLINE const Type& MVector2D<Type>::operator[](SIZE_T Index) const&
    {
      me_assert((Index >= 0) && (Index < 2));

      return XY[Index];
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return copy of component
     */
    template<typename Type>
    FORCEINLINE Type MVector2D<Type>::operator[](SIZE_T Index) const&&
    {
      me_assert((Index >= 0) && (Index < 2));
      
      return XY[Index];
    }
  }
}

#ifdef _MSC_VER
#pragma warning (pop) // (disable : 4459) (disable : 4544) (disable : 4201)
#endif

#endif // MENGINE_MATH_VECTOR2D