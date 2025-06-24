#pragma once

//
// NOTE: Inline file of Vector.h to seperate declaration and implementation
//

#ifndef __ME__CORE__VECTOR2D__INL__
#define __ME__CORE__VECTOR2D__INL__

#include "Misc/CoreDefines.h"
#include "Math/MathForward.h"
    
namespace MEngine
{
  namespace Math
  {
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
      const Type RealScale = static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (LhsV.X * RealScale),
                (LhsV.Y * RealScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type> operator*(ScaleType Scale, const MVector2D<Type>& RhsV)
    {
      const Type RealScale = static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (RhsV.X * RealScale),
                (RhsV.Y * RealScale)
             };
    }

    template<typename Type, typename ScaleType, TEMPLATE_CONDITION_DEFINITION(std::is_arithmetic_v<ScaleType>)>
    FORCEINLINE MVector2D<Type> operator/(const MVector2D<Type>& V, ScaleType Scale)
    {
      const Type RealScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      return MVector2D<Type>
             {
                (V.X * RealScale),
                (V.Y * RealScale)
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
      const Type RealScale = static_cast<Type>(1) / static_cast<Type>(Scale);
      
      X *= RealScale;
      Y *= RealScale;

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
    
#endif // __ME__CORE__VECTOR2D__INL__