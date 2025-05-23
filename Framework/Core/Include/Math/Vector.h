// MEngine vector definition
#pragma once

#ifndef MENGINE_MATH_VECTOR
#define MENGINE_MATH_VECTOR

#include <cassert>
#include <type_traits>

#include "HAL/Platform.h"
#include "Macro/ClassMacroHelpers.h"
#include "Macro/AssertionMacros.h"
#include "Math/MathForward.h"
#include "Math/Axis.h"
#include "Math/MEngineMathUtility.h"
#include "Misc/CoreDefines.h"
#include "Templates/METypeAmbiguityResolve.h"
#include "Templates/METypeTraits.h"

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
      CORE_API static const MVector<Type> ZeroVector;

      // one vector(1, 1, 1)
      CORE_API static const MVector<Type> OneVector;

      // MEngine right vector (1, 0, 0)
      CORE_API static const MVector<Type> RightVector;

      // MEngine left vector (-1, 0, 0)
      CORE_API static const MVector<Type> LeftVector;

      // MEngine up vector (0, 1, 0)
      CORE_API static const MVector<Type> UpVector;

      // MEngine down vector (0, -1, 0)
      CORE_API static const MVector<Type> DownVector;

      // MEngine forward vector (0, 0, 1)
      CORE_API static const MVector<Type> ForwardVector;

      // MEngine backward vector (0, 0, -1)
      CORE_API static const MVector<Type> BackwardVector;

      // Unit X axis vector (1, 0, 0)
      CORE_API static const MVector<Type> XAxisVector;

      // Unit Y axis vector (0, 1, 0)
      CORE_API static const MVector<Type> YAxisVector;

      // Unit Z axis vector (0, 0, 1)
      CORE_API static const MVector<Type> ZAxisVector;

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

      static FORCEINLINE MVector<Type> Right()
      {
        return RightVector;
      }

      static FORCEINLINE MVector<Type> Left()
      {
        return LeftVector;
      }

      static FORCEINLINE MVector<Type> Up()
      {
        return UpVector;
      }

      static FORCEINLINE MVector<Type> Down()
      {
        return DownVector;
      }

      static FORCEINLINE MVector<Type> Forward()
      {
        return ForwardVector;
      } 

      static FORCEINLINE MVector<Type> Backward()
      {
        return BackwardVector;
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

      /**
       * Convert different type vector to this type
       */
      template<typename DiffType, TEMPLATE_CONDITION_DECLARATION(!std::is_same_v<Type, DiffType>)>
      explicit MVector(IN const MVector<DiffType>& Other);

      // end of Constructors

      /**
       * Calculate cross product
       * 
       * @param OtherV The other vector
       * @return The cross product
       */
      FORCEINLINE MVector<Type> Cross(IN const ThisClass& OtherV) const;

      /**
       * Calculate cross product of two vectors
       * 
       * @param V1 The first vector
       * @param V2 The second vector
       * @return The cross product
       */
      FORCEINLINE static MVector<Type> CrossProduct(IN const ThisClass& V1, IN const ThisClass& V2);

      /**
       * Calculate dot product
       * 
       * @param OtherV The other vector
       * @return The dot product
       */
      FORCEINLINE Type Dot(IN const ThisClass& OtherV) const;

      /**
       * Calculate dot product of two vectors
       * 
       * @param V1 The first vector
       * @param V2 The second vector
       * @return The dot product
       */
       FORCEINLINE static Type DotProduct(IN const ThisClass& V1, IN const ThisClass& V2);

      private:
        /**
         * INNER FUNCTION
         * Calculate cross product
         * 
         * @param OtherV The other vector
         * @return The cross product
         */
        FORCEINLINE MVector<Type> CrossInner(IN const ThisClass& OtherV) const;

        /**
         * INNER FUNCTION
         * Calculate dot product
         * 
         * @param OtherV The other vector
         * @return The dot product
         */
        FORCEINLINE Type DotInner(IN const ThisClass& OtherV) const;

      public:

        /**
         * Check against another vector for equality
         * 
         * @param OtherV The other vector to check
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE bool Equals(IN const ThisClass& OtherV, DEFAULT_VAR Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        static FORCEINLINE bool Equals(IN const MVector<Type>& V1, IN const MVector<Type>& V2, DEFAULT_VAR Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL);

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
        FORCEINLINE bool IsNearlyZero(DEFAULT_VAR Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

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
        FORCEINLINE bool Normalize(DEFAULT_VAR Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL);
        
        /**
         * Gets normalized version of this vector if it's magnitude is larger than a tolerance, return ZeroVector if not
         * 
         * @param Tolerance Error Tolerance
         * @return A normalized copy of this vector if success, ZeroVector otherwise
         */
        FORCEINLINE MVector<Type> GetNormalizedCopy(DEFAULT_VAR Type Tolerance = MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Gets projection vector based on other vector
         * 
         * @param V Vector to project onto
         * @return Projected vector
         */
        FORCEINLINE MVector<Type> ProjectOnTo(IN const ThisClass& V) const;
        
        /**
         * Gets projection vector based on specific axis
         * 
         * @param Axis Enum of axis
         * @return Projected vector
         */
        FORCEINLINE MVector<Type> ProjectOnToAxis(IN EAxis Axis) const;

        /**
         * Gets projection vector of target vector based on other vector
         * 
         * @param TargetV The target vector
         * @param OnToV Vector to project onto
         * @return Projected vector
         */
        static FORCEINLINE MVector<Type> Projection(IN const ThisClass& TargetV, IN const ThisClass& OnToV);


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
        friend FORCEINLINE MVector<Type> operator+(IN const MVector<Type>& V1, IN const MVector<Type>& V2);

        /**
         * Gets the result of component-wise subtraction of two vectors
         *
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector subtraction
         */
        friend FORCEINLINE MVector<Type> operator-(IN const MVector<Type>& V1, IN const MVector<Type>& V2);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param LhsV The left-head side vector
         * @param Scale Value to multiply each component
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator*(IN const MVector<Type>& LhsV, IN ScaleType Scale);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param Scale Value to multiply each component
         * @param RhsV The right-head side vector
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator*(IN ScaleType Scale, IN const MVector<Type>& RhsV);

        /**
         * Gets the result of dividing each component by scale
         * 
         * @param V The vector
         * @param Scale Value to divide each component
         * @return The result of multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        friend FORCEINLINE MVector<Type> operator/(IN const MVector<Type>& V, IN ScaleType Scale);

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are component qual, false otherwise
         */
        friend FORCEINLINE bool operator==(IN const MVector<Type>& V1, IN const MVector<Type>& V2);

        /**
         * Check two vectors for inequality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are not component equal, false otherwise
         */
        friend FORCEINLINE bool operator!=(IN const MVector<Type>& V1, IN const MVector<Type>& V2);

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
        FORCEINLINE MVector<Type>& operator+=(IN const ThisClass& OtherV);

        /**
         * Subtracts another vector to this vector
         * Component-wise subtraction
         * 
         * @param OtherV Vector to subtract from this
         * @return This vector after subtraction
         */
        FORCEINLINE MVector<Type>& operator-=(IN const ThisClass& OtherV);

        /**
         * Multiply this vector
         * Component-wise multiplication
         * 
         * @param Scale Value to multiply each component
         * @return This vector after Multiplication
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector<Type>& operator*=(IN ScaleType Scale);

        /**
         * Divide this vector
         * Component-wise Dividing
         * 
         * @param Scale Value to divide each component
         * @return This vector after Dividing
         */
        template<typename ScaleType, TEMPLATE_CONDITION_DECLARATION(std::is_arithmetic_v<ScaleType>)>
        FORCEINLINE MVector<Type>& operator/=(IN ScaleType Scale);

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return reference to component
         */
        FORCEINLINE Type& operator[](IN SIZE_T Index) &;

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return const reference to component
         */
        FORCEINLINE const Type& operator[](IN SIZE_T Index) const&;

        /**
         * Gets specific component of vector
         * 
         * @param Index the index of vector component
         * @return copy of component
         */
        FORCEINLINE Type operator[](IN SIZE_T Index) const&&;
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
    template<typename DiffType, TEMPLATE_CONDITION_DEFINITION(!std::is_same_v<Type, DiffType>)>
    MVector<Type>::MVector(const MVector<DiffType>& Other)
      : MVector<Type>((Type)Other.X, (Type)Other.Y, (Type)Other.Z)
    {}

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::Cross(const ThisClass& OtherV) const
    {
      return CrossInner(OtherV);
    }

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::CrossProduct(const ThisClass& V1, const ThisClass& V2)
    {
      return V1.CrossInner(V2);
    } 

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::CrossInner(const ThisClass& OtherV) const
    {
      return MVector<Type>
             {
                Y * OtherV.Z - Z * OtherV.X,
                Z * OtherV.X - X * OtherV.Z,
                X * OtherV.Y - Y * OtherV.X
             };
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::Dot(const ThisClass& OtherV) const
    {
      return DotInner(OtherV);
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::DotProduct(const ThisClass& V1, const ThisClass& V2)
    {
      return V1.DotInner(V2);
    } 

    template<typename Type>
    FORCEINLINE Type MVector<Type>::DotInner(const ThisClass& OtherV) const
    {
      return (X * OtherV.X) + (Y * OtherV.Y) + (Z * OtherV.Z);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::Equals(const ThisClass& OtherV, Type Tolerance) const
    {
      return (MMath::Abs(X - OtherV.X) <= Tolerance) && (MMath::Abs(Y - OtherV.Y) <= Tolerance) && (MMath::Abs(Z - OtherV.Z) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::Equals(const ThisClass& V1, const ThisClass& V2, Type Tolerance)
    {
      return (MMath::Abs(V1.X - V2.X) <= Tolerance) && (MMath::Abs(V1.Y - V2.Y) <= Tolerance) && (MMath::Abs(V1.Z - V2.Z) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::IsZero() const
    {
      return (X == 0) && (Y == 0) && (Z == 0);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::IsNearlyZero(Type Tolerance) const
    {
      return (MMath::Abs(X) <= Tolerance) &&
             (MMath::Abs(Y) <= Tolerance) &&
             (MMath::Abs(Z) <= Tolerance);
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::Magnitude() const
    {
      return MMath::Sqrt(SquaredMagnitude());
    }

    template<typename Type>
    FORCEINLINE Type MVector<Type>::SquaredMagnitude() const
    {
      return (X * X) + (Y * Y) + (Z * Z);
    }

    template<typename Type>
    FORCEINLINE bool MVector<Type>::IsNormalized() const
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
    FORCEINLINE bool MVector<Type>::Normalize(Type Tolerance)
    {
      const Type squaredMag = SquaredMagnitude();
      if (squaredMag <= Tolerance)
      {
        return false;
      } 

      const Type realScale = static_cast<Type>(1) / MMath::Sqrt(squaredMag);

      X *= realScale;
      Y *= realScale;
      Z *= realScale;
      return true;
    }
    
    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::GetNormalizedCopy(Type Tolerance) const
    {
      const Type squaredMag = SquaredMagnitude();
      if (squaredMag <= Tolerance)
      {
        return ZeroVector;
      }

      const Type realScale = static_cast<Type>(1) / MMath::Sqrt(squaredMag);
      return MVector<Type>
             {
                (X * realScale),
                (Y * realScale),
                (Z * realScale)
             };
    }

    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::ProjectOnTo(const ThisClass& V) const
    {
      return (Dot(V) / V.SquaredMagnitude()) * V;
    }
    
    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::ProjectOnToAxis(EAxis Axis) const
    {
      using enum EAxis;
      switch (Axis)
      {
        case X:
          return ProjectOnTo(XAxisVector);
        case Y:
          return ProjectOnTo(YAxisVector);
        case Z:
          return ProjectOnTo(ZAxisVector);
        case XNegative:
          return ProjectOnTo(-XAxisVector);
        case YNegative:
          return ProjectOnTo(-YAxisVector);
        case ZNegative:
          return ProjectOnTo(-ZAxisVector);
        default:
          return ZeroVector;
      }
    }
    
    template<typename Type>
    FORCEINLINE MVector<Type> MVector<Type>::Projection(const ThisClass& TargetV, const ThisClass& OnToV)
    {
      return TargetV.ProjectOnTo(OnToV);
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

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
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

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
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

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
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
    template<typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
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
    template<typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
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

#endif // MENGINE_MATH_VECTOR