#pragma once

#ifndef _ME_CORE_MATH_VECTOR4_
#define _ME_CORE_MATH_VECTOR4_

#include "Misc/CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"                  // available in C++20
#include "Templates/IsDifferentFloatingTypeTraits.h"

#include "Math/Vector.h"

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

namespace MEngine
{
  namespace Math
  {
    /**
     * @brief 4D vector
     * 
     * @tparam FloatingType Component type of this 4D vector
     * @param AlignSize alignment size for SIMD use
     */
    template<FLOATING_TYPE_CONCEPT FloatingType, uint32 AlignSize = 16>
    struct alignas(AlignSize) MVector4
    {
      #if !CAN_USE_CONCEPT
        static_assert(std::is_floating_point_v<FloatingType>, "Vector4 type must be floating point");
      #endif

      public:
        TYPEDEF(FloatingType, Type);
        #define COMMA ,
        GENERATE_CLASS_DEF(MVector4<Type COMMA AlignSize>);
        #undef COMMA

        union
        {
          struct
          {
            /**Vector4's X component */
            Type X;

            /**Vector4's Y component */
            Type Y;

            /**Vector4's Z component */
            Type Z;

            /**Vector4's W component */
            Type W;
          };

          /**Internal use */ 
          Type XYZW[4];
        };

        /**
         * Static member for general use
         */

        /**Zero vector(0, 0, 0, 0) */
        CORE_API static const MVector4<Type, AlignSize> ZeroVector;

        /**One vector(1, 1, 1, 1) */
        CORE_API static const MVector4<Type, AlignSize> OneVector;

        /**
         * Static method for general use
         */
        FORCEINLINE static MVector4 Zero()
        {
          return ZeroVector;
        }

        FORCEINLINE static MVector4 One()
        {
          return OneVector;
        }

        /**
         * Constructors
         */

        /**
         * @brief Default constructor. Set all components to 0
         * 
         */
        FORCEINLINE explicit MVector4();

        /**
         * @brief Construct Vector4 with Vector3's XYZ and W with 1.0
         * 
         * @param V3 Vector3 to set Vector4's XYZ    
         */
        FORCEINLINE explicit MVector4(IN const MVector<Type>& V3);

        /**
         * @brief Construct Vector4 with Vector3's XYZ and W with Arg
         * 
         * @param V3 Vector3 to set Vector4's XYZ
         * 
         * @tparam WValue Argument to set W
         */
        TEMPLATE_REQUIRES_DECLARATION(typename ArgType, std::is_arithmetic_v<ArgType>)
        FORCEINLINE MVector4(IN const MVector<Type>& V3, ArgType WValue);

        /**
         * @brief Construct Vector4 with 4 components
         * 
         * @param InX X component
         * @param InY Y component
         * @param InZ Z component
         * @param InW W component, has a default value of 1
         */
        FORCEINLINE MVector4(IN Type InX, IN Type InY, IN Type InZ , DEFAULT_VAR Type InW = (Type)1.0);

        /**
         * @brief Construct Vector4 with different type of Type
         * 
         * @tparam DiffType Different type from current Vector4 type
         * @tparam OtherAlignSize
         * @param Other Different type Vector4 
         */
        template<FLOATING_TYPE_CONCEPT DiffType, uint32 OtherAlignSize, TEMPLATE_CONDITION_DECLARATION(MEngine::TypeTraits::IsDifferentFloatingType_V<Type, DiffType>)>
        FORCEINLINE explicit MVector4(IN const MVector4<DiffType, OtherAlignSize>& Other);

        // End of Constructors

        /**
         * Check against another vector for equality
         * 
         * @param OtherV The other vector to check
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE bool Equals(IN const ThisClass& OtherV, DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Check against another vector for XYZ component's equality
         * 
         * @param OtherV The other vector to check
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE bool EqualsXYZ(IN const ThisClass& OtherV, DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        
        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE static bool Equals(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL);
        
        /**
         * Check two vector's XYZ component for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @param Tolerance Error Tolerance
         * @return true if the vectors are equal within tolerance limits, false otherwise
         */
        FORCEINLINE static bool EqualsXYZ(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL);
        
        /**
         * Check if this vector's XYZ component is normalized
         * 
         * @return true if normalized, false otherwise
         */
        FORCEINLINE bool IsNormalizedXYZ(DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Normalize this vector's XYZ component if it's magnitude is larger than a tolerance and set W to 0, leaves it unchange if not
         * 
         * @param Tolerance Error Tolerance
         * @return true if normalize successfully, false otherwise
         */
        FORCEINLINE bool NormalizeXYZ(DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL);
        
        /**
         * Gets normalized version of this vector if it's magnitude is larger than a tolerance, return ZeroVector if not
         * 
         * @param Tolerance Error Tolerance
         * @return A normalized copy of this vector if success, ZeroVector otherwise
         */
        FORCEINLINE MVector4<Type, AlignSize> GetNormalizedXYZCopy(DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Get the magnitude of this vector's XYZ component
         * 
         * @return The magnitude of this vector's XYZ component
         */
        FORCEINLINE Type MagnitudeXYZ() const;

        /**
         * Get the squared magnitude of this vector's XYZ component
         * 
         * @return The squared magnitude of this vector's XYZ component
         */
        FORCEINLINE Type SquaredMagnitudeXYZ() const;

        /**
         * Get the magnitude of this vector with W component
         * 
         * @return The magnitude of this vector with W component
         */
        FORCEINLINE Type Magnitude() const;

        /**
         * Get the squared magnitude of this vector with W component
         * 
         * @return The squared magnitude of this vector with W component
         */
        FORCEINLINE Type SquaredMagnitude() const;

        /**
         * Check all components of the vector's XYZ component is nearly zero within tolerance
         * 
         * @param Tolerance Error Tolerance
         * @return true if the vector's XYZ component is near to zero, false otherwise
         */
        FORCEINLINE bool IsNearlyZeroXYZ(DEFAULT_VAR Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

      public:
        /**
         * Operator overload
         */

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

        /**
         * Get a affirmed copy of this vector
         * same as this
         * 
         * @return A affirmed copy of this
         */
        FORCEINLINE MVector4<Type, AlignSize> operator+() const;

        /**
         * Get a negated copy of this vector
         * 
         * @return A negated copy of this
         */
        FORCEINLINE MVector4<Type, AlignSize> operator-() const;

        /**
         * Check two vectors for equality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are component qual, false otherwise
         */
        friend FORCEINLINE bool operator==(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2);

        /**
         * Check two vectors for inequality
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return true if the vectors are not component equal, false otherwise
         */
        friend FORCEINLINE bool operator!=(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2);

        /**
         * Gets the result of component-wise addition of two vectors
         * 
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector addition
         */
        friend FORCEINLINE MVector4<Type, AlignSize> operator+(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2);

        /**
         * Gets the result of component-wise subtraction of two vectors
         *
         * @param V1 The first vector
         * @param V2 The second vector
         * @return The result of vector subtraction
         */
        friend FORCEINLINE MVector4<Type, AlignSize> operator-(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param LhsV The left-head side vector
         * @param Scale Value to multiply each component
         * @return The result of multiplication
         */
        TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
        friend FORCEINLINE MVector4<Type, AlignSize> operator*(IN const MVector4<Type, AlignSize>& LhsV, IN ScaleType Scale);

        /**
         * Gets the result of multiplying each component by scale
         * 
         * @param Scale Value to multiply each component
         * @param RhsV The right-head side vector
         * @return The result of multiplication
         */
        TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
        friend FORCEINLINE MVector4<Type, AlignSize> operator*(IN ScaleType Scale, IN const MVector4<Type, AlignSize>& RhsV);

        /**
         * Gets the result of dividing each component by scale
         * 
         * @param V The vector
         * @param Scale Value to divide each component
         * @return The result of multiplication
         */
        TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
        friend FORCEINLINE MVector4<Type, AlignSize> operator/(IN const MVector4<Type, AlignSize>& V, IN ScaleType Scale);

        /**
         * Adds another vector to this vector
         * Component-wise addition
         * 
         * @param OtherV Vector to add from this
         * @return This vector after addition
         */
        FORCEINLINE MVector4<Type, AlignSize>& operator+=(IN const ThisClass& OtherV);

        /**
         * Subtracts another vector to this vector
         * Component-wise subtraction
         * 
         * @param OtherV Vector to subtract from this
         * @return This vector after subtraction
         */
        FORCEINLINE MVector4<Type, AlignSize>& operator-=(IN const ThisClass& OtherV);

        /**
         * Multiply this vector
         * Component-wise multiplication
         * 
         * @param Scale Value to multiply each component
         * @return This vector after Multiplication
         */
        TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
        FORCEINLINE MVector4<Type, AlignSize>& operator*=(IN ScaleType Scale);

        /**
         * Divide this vector
         * Component-wise Dividing
         * 
         * @param Scale Value to divide each component
         * @return This vector after Dividing
         */
        TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
        FORCEINLINE MVector4<Type, AlignSize>& operator/=(IN ScaleType Scale);

    };

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>::MVector4()
      : X(static_cast<Type>(0))
      , Y(static_cast<Type>(0))
      , Z(static_cast<Type>(0))
      , W(static_cast<Type>(0))
    {
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>::MVector4(IN const MVector<Type>& V3)
      : X(V3.X)
      , Y(V3.Y)
      , Z(V3.Z)
      , W(static_cast<Type>(1))
    {
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    TEMPLATE_REQUIRES_DEFINITION(typename ArgType, std::is_arithmetic_v<ArgType>)
    FORCEINLINE MVector4<Type, AlignSize>::MVector4(IN const MVector<Type>& V3, ArgType WValue)
      : X(V3.X)
      , Y(V3.Y)
      , Z(V3.Z)
      , W(static_cast<Type>(WValue))
    {
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>::MVector4(IN Type InX, IN Type InY, IN Type InZ , DEFAULT_VAR Type InW)
      : X(InX)
      , Y(InY)
      , Z(InZ)
      , W(InW)
    {
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    template<FLOATING_TYPE_CONCEPT DiffType, uint32 OtherAlignSize, TEMPLATE_CONDITION_DEFINITION(MEngine::TypeTraits::IsDifferentFloatingType_V<Type, DiffType>)>
    FORCEINLINE MVector4<Type, AlignSize>::MVector4(IN const MVector4<DiffType, OtherAlignSize>& Other)
      : X(Other.X)
      , Y(Other.Y)
      , Z(Other.Z)
      , W(Other.W)
    {
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::Equals(IN const MVector4<Type, AlignSize>& OtherV, DEFAULT_VAR Type Tolerance) const
    {
      return   EqualsXYZ(OtherV, Tolerance)
            && (MMath::Abs(W - OtherV.W) <= Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::EqualsXYZ(IN const MVector4<Type, AlignSize>& OtherV, DEFAULT_VAR Type Tolerance) const
    {
      return   (MMath::Abs(X - OtherV.X) <= Tolerance)
            && (MMath::Abs(Y - OtherV.Y) <= Tolerance)
            && (MMath::Abs(Z - OtherV.Z) <= Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::Equals(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, DEFAULT_VAR Type Tolerance)
    {
      return V1.Equals(V2, Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::EqualsXYZ(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, DEFAULT_VAR Type Tolerance)
    {
      return V1.EqualsXYZ(V2, Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::IsNormalizedXYZ(DEFAULT_VAR Type Tolerance) const
    {
      return MMath::Abs(static_cast<Type>(1.0) - MagnitudeXYZ()) <= Tolerance;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::NormalizeXYZ(DEFAULT_VAR Type Tolerance)
    {
      const Type squaredMagXYZ = SquaredMagnitudeXYZ();
      if (squaredMagXYZ <= Tolerance)
      {
        return false;
      }

      const Type realScale = static_cast<Type>(1.0) / MMath::Sqrt(squaredMagXYZ);

      X *= realScale;
      Y *= realScale;
      Z *= realScale;
      return true;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize> MVector4<Type, AlignSize>::GetNormalizedXYZCopy(DEFAULT_VAR Type Tolerance) const
    {
      const Type squaredMagXYZ = SquaredMagnitudeXYZ();
      if (squaredMagXYZ <= Tolerance)
      {
        return ZeroVector;
      }

      const Type realScale = static_cast<Type>(1.0) / MMath::Sqrt(squaredMagXYZ);

      return MVector4<Type, AlignSize>
              {
                X * realScale, 
                Y * realScale, 
                Z * realScale, 
                W * realScale
              };
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MVector4<Type, AlignSize>::MagnitudeXYZ() const
    {
      return MMath::Sqrt(SquaredMagnitudeXYZ());
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MVector4<Type, AlignSize>::SquaredMagnitudeXYZ() const
    {
      return (X * X) + (Y * Y) + (Z * Z);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MVector4<Type, AlignSize>::Magnitude() const
    {
      return MMath::Sqrt(SquaredMagnitude());
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MVector4<Type, AlignSize>::SquaredMagnitude() const
    {
      return (X * X) + (Y * Y) + (Z * Z) + (W * W);
    }
    
    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MVector4<Type, AlignSize>::IsNearlyZeroXYZ(DEFAULT_VAR Type Tolerance) const
    {
      return   (MMath::Abs(X) <= Tolerance)
            && (MMath::Abs(Y) <= Tolerance)
            && (MMath::Abs(Z) <= Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type& MVector4<Type, AlignSize>::operator[](IN SIZE_T Index) &
    {
      me_assert((Index >= 0) && (Index < 4));

      return XYZW[Index];
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE const Type& MVector4<Type, AlignSize>::operator[](IN SIZE_T Index) const&
    {
      me_assert((Index >= 0) && (Index < 4));

      return XYZW[Index];
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MVector4<Type, AlignSize>::operator[](IN SIZE_T Index) const&&
    {
      me_assert((Index >= 0) && (Index < 4));

      return XYZW[Index];
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize> MVector4<Type, AlignSize>::operator+() const
    {
      return *this;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>MVector4<Type, AlignSize>::operator-() const
    {
      return MVector4<Type, AlignSize>{-X, -Y, -Z, -W};
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool operator==(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2)
    {
      return   (V1.X == V2.X)
            && (V1.Y == V2.Y)
            && (V1.Z == V2.Z)
            && (V1.W == V2.W);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool operator!=(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2)
    {
      return !(V1 == V2);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize> operator+(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2)
    {
      return MVector4<Type, AlignSize>
              {
                (V1.X + V2.X),
                (V1.Y + V2.Y),
                (V1.Z + V2.Z),
                (V1.W + V2.W)
              };
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize> operator-(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2)
    {
      return MVector4<Type, AlignSize>
              {
                (V1.X - V2.X),
                (V1.Y - V2.Y),
                (V1.Z - V2.Z),
                (V1.W - V2.W)
              };
    }

    template <FLOATING_TYPE_CONCEPT Type, uint32 AlignSize, MEngine::Concepts::ArithmeticTypeConcept ScaleType> 
      requires std::is_arithmetic_v<ScaleType>
    FORCEINLINE MVector4<Type, AlignSize> operator*(IN const MVector4<Type, AlignSize>& LhsV, IN ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(Scale);
      return MVector4<Type, AlignSize>
        {
          LhsV.X * realScale,
          LhsV.Y * realScale,
          LhsV.Z * realScale,
          LhsV.W * realScale
        };
    }

    template <FLOATING_TYPE_CONCEPT Type, uint32 AlignSize, MEngine::Concepts::ArithmeticTypeConcept ScaleType> 
      requires std::is_arithmetic_v<ScaleType>
    FORCEINLINE MVector4<Type, AlignSize> operator*(IN ScaleType Scale, IN const MVector4<Type, AlignSize>& RhsV)
    {
      return RhsV * Scale;
    }

    template <FLOATING_TYPE_CONCEPT Type, uint32 AlignSize, MEngine::Concepts::ArithmeticTypeConcept ScaleType> 
      requires std::is_arithmetic_v<ScaleType>
    FORCEINLINE MVector4<Type, AlignSize> operator/(IN const MVector4<Type, AlignSize>& V, IN ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(1.0)/ static_cast<Type>(Scale);

      return MVector4<Type, AlignSize>
              {
                V.X * realScale,
                V.Y * realScale,
                V.Z * realScale,
                V.W * realScale
              };
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>& MVector4<Type, AlignSize>::operator+=(IN const ThisClass& OtherV)
    {
      X += OtherV.X;
      Y += OtherV.Y;
      Z += OtherV.Z;
      W += OtherV.W;

      return *this;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MVector4<Type, AlignSize>& MVector4<Type, AlignSize>::operator-=(IN const ThisClass& OtherV)
    {
      X -= OtherV.X;
      Y -= OtherV.Y;
      Z -= OtherV.Z;
      W -= OtherV.W;

      return *this;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
    FORCEINLINE MVector4<Type, AlignSize>& MVector4<Type, AlignSize>::operator*=(IN ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(Scale);

      X *= realScale;
      Y *= realScale;
      Z *= realScale;
      W *= realScale;

      return *this;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    TEMPLATE_REQUIRES_DECLARATION(ARITHMETIC_TYPE_CONCEPT ScaleType, std::is_arithmetic_v<ScaleType>)
    FORCEINLINE MVector4<Type, AlignSize>& MVector4<Type, AlignSize>::operator/=(IN ScaleType Scale)
    {
      const Type realScale = static_cast<Type>(1.0) / static_cast<Type>(Scale);

      X *= realScale;
      Y *= realScale;
      Z *= realScale;
      W *= realScale;

      return *this;
    }
  }
}

#ifdef _MSC_VER
#pragma warning (pop) // (disable : 4459) (disable : 4544) (disable : 4201)
#endif // _MSC_VER

#endif // _ME_CORE_MATH_VECTOR4_