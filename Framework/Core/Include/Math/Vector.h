// MEngine vector definition
#pragma once

#ifndef _ME_CORE_MATH_VECTOR_
#define _ME_CORE_MATH_VECTOR_

#include "CoreDefines.h"
#include "HAL/Platform.h"
#include "Macro/ClassMacroHelpers.h"
#include "Macro/AssertionMacros.h"
#include "Math/MathForward.h"
#include "Math/Axis.h"
#include "Math/MEngineMathUtility.h"
#include "Templates/METypeAmbiguityResolve.h"
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
  }
}

// Include vector inline implementation file
#include "Math/Vector.inl"

#ifdef _MSC_VER
#pragma warning (pop) // (disable : 4459) (disable : 4544) (disable : 4201)
#endif

#endif // _ME_CORE_VECTOR_