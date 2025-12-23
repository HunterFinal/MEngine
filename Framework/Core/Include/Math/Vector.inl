#pragma once

//
// NOTE: Inline file of Vector.h to seperate declaration and implementation
//

#ifndef __ME__CORE__VECTOR__INL__
#define __ME__CORE__VECTOR__INL__

namespace MEngine
{
  namespace Math
  {
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
    FORCEINLINE MVector<Type>::MVector(const MVector<DiffType>& Other)
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
      me_assert((Index >= 0) && (Index < 3));
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
      me_assert((Index >= 0) && (Index < 3));

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
      me_assert((Index >= 0) && (Index < 3));
      
      return XYZ[Index];
    }
  }
}

#endif 