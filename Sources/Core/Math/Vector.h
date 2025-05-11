// MEngine Vector

#ifdef _WIN32
#pragma once
#endif


#ifndef MENGINE_VECTOR
#define MENGINE_VECTOR

#include <cassert>
#include <type_traits>

#include "Math/MathForward.h"

#ifdef _MSC_VER
#pragma warning (push)
// テンプレート関数がグローバル変数に対してShadowing　warningsを生成することを防ぐ
// Ensure template functions don't generate shadowing warnings against global variables at the point of instantiation
#pragma warning (disable : 4459)
// MSVCの仕様により、無名テンプレート引数 + デフォルト値が無視される警告メッセージ生成を防ぐ
// Ensure Nameless template variable with default value don't generate warnings in MSVC
#pragma warning (disable : 4544)
#endif

// MEngine namespace
namespace MEngine
{
  // MEngine::Math namespace
  namespace Math
  {
    template<typename FloatingType>
    struct MVector
    {
      static_assert(std::is_floating_point_v<FloatingType>, "Vector type must be floating point");
      
      
      public:
        TYPEDEF(FloatingType, Type);
        GENERATE_CLASS_DEF(MVector<Type>);
        
      union
      {
        struct
        {
          // Vector's X component;
          Type X;

          // Vector's Y component;
          Type Y;

          // Vector's Z component;
          Type Z;
        };

        // internal use
        Type XYZ[3];
      };

      // zero vector(0, 0, 0)
      static const MVector<Type> ZeroVector;

      // one vector(1, 1, 1)
      static const MVector<Type> OneVector;

      // MEngine right vector (1, 0, 0)
      static const MVector<Type> RightVector;

      // MEngine left vector (-1, 0, 0)
      static const MVector<Type> LeftVector;

      // MEngine up vector (0, 1, 0)
      static const MVector<Type> UpVector;

      // MEngine down vector (0, -1, 0)
      static const MVector<Type> DownVector;

      // MEngine forward vector (0, 0, 1)
      static const MVector<Type> ForwardVector;

      // MEngine backward vector (0, 0, -1)
      static const MVector<Type> BackwardVector;

      // Unit X axis vector (1, 0, 0)
      static const MVector<Type> XAxisVector;

      // Unit Y axis vector (0, 1, 0)
      static const MVector<Type> YAxisVector;

      // Unit Z axis vector (0, 0, 1)
      static const MVector<Type> ZAxisVector;

      // -----------------
      // static method
      // -----------------
      static FORCEINLINE MVector<Type> Zero() 
      {
        return ZeroVector;
      } 

      static FORCEINLINE MVector<Type> One()
      {
        return OneVector;
      }

      static FORCEINLINE MVector<Type> UnitX()
      {
        return XAxisVector;
      }

      static FORCEINLINE MVector<Type> UnitY()
      {
        return YAxisVector;
      }

      static FORCEINLINE MVector<Type> UnitZ()
      {
        return ZAxisVector;
      }

      // ---------------
      // Constructors
      // ---------------

      // default Constructors
      FORCEINLINE MVector();

      /** 
       * using initial values for each component
       *
       * @param InX X coord
       * @param InY Y coord
       * @param InZ Z coord
       */
      FORCEINLINE MVector(IN Type InX, IN Type InY, IN Type InZ);

      // end of Constructors

      /**
       * Calculate cross product
       * 
       * @param OtherV The other vector
       * @return The cross product
       */
      FORCEINLINE MVector<Type> Cross(const ThisClass& OtherV) const;

      /**
       * Calculate cross product of two vectors
       * 
       * @param V1 The first vector
       * @param V2 The second vector
       * @return The cross product
       */
      FORCEINLINE static MVector<Type> CrossProduct(const ThisClass& V1, const ThisClass& V2);

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
         * Calculate cross product
         * 
         * @param OtherV The other vector
         * @return The cross product
         */
        FORCEINLINE MVector<Type> CrossInner(const ThisClass& OtherV) const;

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
        FORCEINLINE bool Equals(const MVector<Type>& OtherV, Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        static FORCEINLINE bool Equals(const MVector<Type>& V1, const MVector<Type>& V2, Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL);

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
        template<typename Type>
        friend FORCEINLINE MVector<Type> operator+(const ThisClass& V1, const ThisClass& V2);

        /**
         * Gets the result of component-wise subtraction of two vectors
         *
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector subtraction
         */
        template<typename Type>
        friend FORCEINLINE MVector<Type> operator-(const ThisClass& V1, const ThisClass& V2);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param LhsV The left-head side vector
         * @param Scale Value to multiply each component
         * @return The result of multiplication
         */
        template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator*(const ThisClass& LhsV, ScaleType Scale);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param Scale Value to multiply each component
         * @param RhsV The right-head side vector
         * @return The result of multiplication
         */
        template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator*(ScaleType Scale, const ThisClass& RhsV);

        /**
         * Gets the result of dividing each component by scale
         * 
         * @param V The vector
         * @param Scale Value to divide each component
         * @return The result of multiplication
         */
        template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator/(const ThisClass& V, ScaleType Scale);

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are equal, false otherwise
         */
        template<typename Type>
        friend FORCEINLINE bool operator==(const ThisClass& V1, const ThisClass& V2);

        /**
         * Check two vectors for inequality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are not equal, false otherwise
         */
        template<typename Type>
        friend FORCEINLINE bool operator!=(const ThisClass& V1, const ThisClass& V2);

        /**
         * Get a affirmed copy of this vector
         * same as this
         * 
         * @return A affirmed copy of this
         */
        FORCEINLINE MVector<Type> operator+() const;

        /**
         * Get a negated copy of this vector
         * 
         * @return A negated copy of this
         */
        FORCEINLINE MVector<Type> operator-() const;

        /**
         * Adds another vector to this vector
         * Component-wise addition
         * 
         * @param OtherV Vector to add from this
         * @return This vector after addition
         */
        FORCEINLINE MVector<Type>& operator+=(const ThisClass& OtherV);

        /**
         * Subtracts another vector to this vector
         * Component-wise subtraction
         * 
         * @param OtherV Vector to subtract from this
         * @return This vector after subtraction
         */
        FORCEINLINE MVector<Type>& operator-=(const ThisClass& OtherV);

        /**
         * Multiply this vector
         * Component-wise multiplication
         * 
         * @param Scale Value to multiply each component
         * @return This vector after Multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector<Type>& operator*=(ScaleType Scale);

        /**
         * Divide this vector
         * Component-wise Dividing
         * 
         * @param Scale Value to divide each component
         * @return This vector after Dividing
         */
        template<typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector<Type>& operator/=(ScaleType Scale);

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
    FORCEINLINE MVector<Type>::MVector()
      : X(0)
      , Y(0)
      , Z(0)
    {}

    template<typename Type>
    FORCEINLINE MVector<Type>::MVector(IN Type InX, IN Type InY, IN Type InZ)
      : X(InX)
      , Y(InY)
      , Z(InZ)
    {}

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::Cross(const MVector<Type>& OtherV) const
    {
      return CrossInner(OtherV);
    }

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::CrossProduct(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return V1.CrossInner(V2);
    } 

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::CrossInner(const MVector<Type>& OtherV) const
    {
      return MVector<Type>
             {
                Y * OtherV.Z - Z * OtherV.X,
                Z * OtherV.X - X * OtherV.Z,
                X * OtherV.Y - Y * OtherV.X
             };
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::Dot(const MVector<Type>& OtherV) const
    {
      return DotInner(OtherV);
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::DotProduct(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return V1.DotInner(V2);
    } 

    template<typename Type>
    FORCEINLINE Type MVector<Type>::DotInner(const MVector<Type>& OtherV) const
    {
      return (X * OtherV.X) + (Y * OtherV.Y) + (Z * OtherV.Z);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::Equals(const MVector<Type>& OtherV, Type Tolerance) const
    {
      return (MMath::Abs(X - OtherV.X) <= Tolerance) && (MMath::Abs(Y - OtherV.Y) <= Tolerance) && (MMath::Abs(Z - OtherV.Z) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::Equals(const MVector<Type>& V1, const MVector<Type>& V2, Type Tolerance)
    {
      return (MMath::Abs(V1.X - V2.X) <= Tolerance) && (MMath::Abs(V1.Y - V2.Y) <= Tolerance) && (MMath::Abs(V1.Z - V2.Z) <= Tolerance);
    }

    // -------------------------------------------------------
    // MVector<Type> operator overload definitions
    // -------------------------------------------------------

    template<typename Type>
    FORCEINLINE MVector<Type> operator+(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return MVector<Type>
             {
                (V1.X + V2.X),
                (V1.Y + V2.Y),
                (V1.Z + V2.Z)              
             };
    }

    template<typename Type>
    FORCEINLINE MVector<Type> operator-(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return MVector<Type>
             {
                (V1.X - V2.X),
                (V1.Y - V2.Y),
                (V1.Z - V2.Z)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector<Type> operator*(const MVector<Type>& LhsV, ScaleType Scale)
    {
      const Type RealScale = static_cast<Type>(Scale);
      return MVector<Type>
             {
                (LhsV.X * RealScale),
                (LhsV.Y * RealScale),
                (LhsV.Z * RealScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector<Type> operator*(ScaleType Scale, const MVector<Type>& RhsV)
    {
      const Type RealScale = static_cast<Type>(Scale);
      return MVector<Type>
             {
                (RhsV.X * RealScale),
                (RhsV.Y * RealScale),
                (RhsV.Z * RealScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector<Type> operator/(const MVector<Type>& V, ScaleType Scale)
    {
      const Type RealScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      return MVector<Type>
             {
                (V.X * RealScale),
                (V.Y * RealScale),
                (V.Z * RealScale)
             };
    }

    template<typename Type>
    FORCEINLINE bool operator==(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return (V1.X == V2.X) && (V1.Y == V2.Y) && (V1.Z == V2.Z);
    }

    template<typename Type>
    FORCEINLINE bool operator!=(const MVector<Type>& V1, const MVector<Type>& V2)
    {
      return !(V1 == V2);
    }

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::operator+() const
    {
      return MVector<Type>{X, Y, Z};
    }

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::operator-() const
    {
      return MVector<Type>{-X, -Y, -Z};
    }

    template<typename Type>
    FORCEINLINE MVector<Type>& MVector<Type>::operator+=(const ThisClass& OtherV)
    {
      X += OtherV.X;
      Y += OtherV.Y;
      Z += OtherV.Z;

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
    FORCEINLINE MVector<Type>& MVector<Type>::operator-=(const ThisClass& OtherV)
    {
      X -= OtherV.X;
      Y -= OtherV.Y;
      Z -= OtherV.Z;

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
    template<typename ScaleType, typename std::enable_if_t<std::is_arithmetic_v<ScaleType>, int>>
    FORCEINLINE MVector<Type>& MVector<Type>::operator*=(ScaleType Scale)
    {
      X *= Scale;
      Y *= Scale;
      Z *= Scale;

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
    template<typename ScaleType, typename std::enable_if_t<std::is_arithmetic_v<ScaleType>, int>>
    FORCEINLINE MVector<Type>& MVector<Type>::operator/=(ScaleType Scale)
    {
      const Type RealScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      
      X *= RealScale;
      Y *= RealScale;
      Z *= RealScale;

      return *this;
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return reference to component
     */
    template<typename Type>
    FORCEINLINE Type& MVector<Type>::operator[](SIZE_T Index) &
    {
      // TODO
      ME_CHECK_IMPL((Index >= 0) && (Index < 3));
      return XYZ[Index];
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return const reference to component
     */
    template<typename Type>
    FORCEINLINE const Type& MVector<Type>::operator[](SIZE_T Index) const&
    {
      // TODO
      ME_CHECK_IMPL((Index >= 0) && (Index < 3));
      return XYZ[Index];
    }

    /**
     * Gets specific component of vector
     * 
     * @param Index the index of vector component
     * @return copy of component
     */
    template<typename Type>
    FORCEINLINE Type MVector<Type>::operator[](SIZE_T Index) const&&
    {
      // TODO
      ME_CHECK_IMPL((Index >= 0) && (Index < 3));
      return XYZ[Index];
    }
  }
}

#ifdef _MSC_VER
#pragma warning (pop) // (disable : 4459) (disable : 4544)
#endif

#endif // MENGINE_VECTOR