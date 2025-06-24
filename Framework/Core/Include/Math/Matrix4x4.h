#pragma once

#ifndef _ME_CORE_MATH_MATRIX_4X4_
#define _ME_CORE_MATH_MATRIX_4X4_

#include "Math/MEngineMathUtility.h"
#include "Math/Vector.h"
#include "Math/Vector4.h"
#include "Misc/CoreDefines.h"
#include "Misc/ConceptsStoragePlace.h"

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
    template<FLOATING_TYPE_CONCEPT FloatingType, uint32 AlignSize = 16>
    struct alignas(AlignSize) MMatrix4x4
    {
      #if !CAN_USE_CONCEPT
        static_assert(std::is_floating_point_v<FloatingType>, "Type of Matrix4x4 must be floating point");
      #endif

      public:
        TYPEDEF(FloatingType, Type);

        #define COMMA ,

        GENERATE_CLASS_DEF(MMatrix4x4<Type COMMA AlignSize>);

        #undef COMMA

        CORE_API static const MMatrix4x4<FloatingType, AlignSize> Identity;

        /**
         * Constructors
         */

        /**
         * Default constructor
         */
        FORCEINLINE explicit MMatrix4x4();

        /**
         * Construct matrix with Vector4
         * 
         * @param V1 X Vector
         * @param V2 Y Vector
         * @param V3 Z Vector
         * @param V4 W Vector
         */
        FORCEINLINE MMatrix4x4(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, IN const MVector4<Type, AlignSize>& V3, IN const MVector4<Type, AlignSize>& V4);

        /**
         * Construct matrix with Vector3
         * 
         * @param V1 X Vector
         * @param V2 Y Vector
         * @param V3 Z Vector
         * @param V4 W Vector
         */
        FORCEINLINE MMatrix4x4(IN const MVector<Type>& V1, IN const MVector<Type>& V2, IN const MVector<Type>& V3, IN const MVector<Type>& V4);

        // End constructors

        /**
         * @brief Set this Matrix to identity
         */
        FORCEINLINE void SetIdentity();

        /**
         * Check against another matrix for equality, with tolerance
         * 
         * @param M The another matrix
         * @param Tolerance Error tolerance
         * @return true if two matrix are equal with tolerance, otherwise false
         */
        FORCEINLINE bool Equals(IN const MMatrix4x4<Type, AlignSize>& M, Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL) const;

        /**
         * Check two matrix for equality, with tolerance
         * 
         * @param M1 The first matrix
         * @param M2 The second matrix
         * @param Tolerance Error tolerance
         * @return true if two matrix are equal with tolerance, otherwise false
         */
        FORCEINLINE static bool Equals(IN const MMatrix4x4<Type, AlignSize>& M1, IN const MMatrix4x4<Type, AlignSize>& M2, Type Tolerance = (Type)MMath::FLOAT_TOLERANCE_KINDA_SMALL);

        /**
         * @brief Transpose this matrix
         * 
         * この行列を自分の転置行列にする
         */
        FORCEINLINE void Transpose();

        /**
         * @brief Get transposed matrix copy
         * 
         * この行列の転置行列のコピーを作る
         */
        FORCEINLINE MMatrix4x4<Type, AlignSize> GetTransposedCopy() const;

        /**
         * @brief Get determinant of this matrix
         * 
         * この行列の行列式を求める
         */
        FORCEINLINE Type GetDeterminant() const;

      public:
        // Matrix( 4 * 4 ) array
        alignas(AlignSize) Type Matrix[4][4];
    };

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MMatrix4x4<Type, AlignSize>::MMatrix4x4()
    {
      const Type zero = static_cast<Type>(0.0f);

      Matrix[0][0] = zero; Matrix[0][1] = zero; Matrix[0][2] = zero; Matrix[0][3] = zero;
      Matrix[1][0] = zero; Matrix[1][1] = zero; Matrix[1][2] = zero; Matrix[1][3] = zero;
      Matrix[2][0] = zero; Matrix[2][1] = zero; Matrix[2][2] = zero; Matrix[2][3] = zero;
      Matrix[3][0] = zero; Matrix[3][1] = zero; Matrix[3][2] = zero; Matrix[3][3] = zero;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MMatrix4x4<Type, AlignSize>::MMatrix4x4(IN const MVector4<Type, AlignSize>& V1, IN const MVector4<Type, AlignSize>& V2, IN const MVector4<Type, AlignSize>& V3, IN const MVector4<Type, AlignSize>& V4)
    {
      Matrix[0][0] = V1.X; Matrix[0][1] = V1.Y; Matrix[0][2] = V1.Z; Matrix[0][3] = V1.W;
      Matrix[1][0] = V2.X; Matrix[1][1] = V2.Y; Matrix[1][2] = V2.Z; Matrix[1][3] = V2.W;
      Matrix[2][0] = V3.X; Matrix[2][1] = V3.Y; Matrix[2][2] = V3.Z; Matrix[2][3] = V3.W;
      Matrix[3][0] = V4.X; Matrix[3][1] = V4.Y; Matrix[3][2] = V4.Z; Matrix[3][3] = V4.W;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MMatrix4x4<Type, AlignSize>::MMatrix4x4(IN const MVector<Type>& V1, IN const MVector<Type>& V2, IN const MVector<Type>& V3, IN const MVector<Type>& V4)
    {
      const Type zero = static_cast<Type>(0.0f);
      const Type one = static_cast<Type>(1.0f);

      Matrix[0][0] = V1.X; Matrix[0][1] = V1.Y; Matrix[0][2] = V1.Z; Matrix[0][3] = zero;
      Matrix[1][0] = V2.X; Matrix[1][1] = V2.Y; Matrix[1][2] = V2.Z; Matrix[1][3] = zero;
      Matrix[2][0] = V3.X; Matrix[2][1] = V3.Y; Matrix[2][2] = V3.Z; Matrix[2][3] = zero;
      Matrix[3][0] = V4.X; Matrix[3][1] = V4.Y; Matrix[3][2] = V4.Z; Matrix[3][3] = one;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE void MMatrix4x4<Type, AlignSize>::SetIdentity()
    {
      const Type zero = static_cast<Type>(0.0f);
      const Type one = static_cast<Type>(1.0f);

      Matrix[0][0] = one ; Matrix[0][1] = zero; Matrix[0][2] = zero; Matrix[0][3] = zero;
      Matrix[1][0] = zero; Matrix[1][1] = one ; Matrix[1][2] = zero; Matrix[1][3] = zero;
      Matrix[2][0] = zero; Matrix[2][1] = zero; Matrix[2][2] = one ; Matrix[2][3] = zero;
      Matrix[3][0] = zero; Matrix[3][1] = zero; Matrix[3][2] = zero; Matrix[3][3] = one;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE bool MMatrix4x4<Type, AlignSize>::Equals(IN const MMatrix4x4<Type, AlignSize>& M, Type Tolerance) const
    {
      for (size_t x = 0; x < 4; ++x)
      {
        for (size_t y = 0; y < 4; ++y)
        {
          if (MMath::Abs(Matrix[x][y] - M[x][y]) > Tolerance)
          {
            return false;
          }
        }
      }

      return true;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE static bool MMatrix4x4<Type, AlignSize>::Equals(IN const MMatrix4x4<Type, AlignSize>& M1, IN const MMatrix4x4<Type, AlignSize>& M2, Type Tolerance)
    {
      return M1.Equals(M2, Tolerance);
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE void MMatrix4x4<Type, AlignSize>::Transpose()
    {
      for (int32 x = 0; x < 4; ++x)
      {
        for (int32 y = x + 1; y < 4; ++y)
        {
          const Type tempValue = Matrix[x][y];
          Matrix[x][y] = Matrix[y][x];
          Matrix[y][x] = tempValue;
        }
      }
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE MMatrix4x4<Type, AlignSize> MMatrix4x4<Type, AlignSize>::GetTransposedCopy() const
    {
      MMatrix4x4<Type, AlignSize> transposedMatrix;

      transposedMatrix.Matrix[0][0] = Matrix[0][0];
      transposedMatrix.Matrix[1][0] = Matrix[0][1];
      transposedMatrix.Matrix[2][0] = Matrix[0][2];
      transposedMatrix.Matrix[3][0] = Matrix[0][3];

      transposedMatrix.Matrix[0][1] = Matrix[1][0];
      transposedMatrix.Matrix[1][1] = Matrix[1][1];
      transposedMatrix.Matrix[2][1] = Matrix[1][2];
      transposedMatrix.Matrix[3][1] = Matrix[1][3];
      
      transposedMatrix.Matrix[0][2] = Matrix[2][0];
      transposedMatrix.Matrix[1][2] = Matrix[2][1];
      transposedMatrix.Matrix[2][2] = Matrix[2][2];
      transposedMatrix.Matrix[3][2] = Matrix[2][3];
      
      transposedMatrix.Matrix[0][3] = Matrix[3][0];
      transposedMatrix.Matrix[1][3] = Matrix[3][1];
      transposedMatrix.Matrix[2][3] = Matrix[3][2];
      transposedMatrix.Matrix[3][3] = Matrix[3][3];

      return transposedMatrix;
    }

    template<FLOATING_TYPE_CONCEPT Type, uint32 AlignSize>
    FORCEINLINE Type MMatrix4x4<Type, AlignSize>::GetDeterminant() const
    {
      return  Matrix[0][0] * 
              (
                  Matrix[1][1] * (Matrix[2][2] * Matrix[3][3] - Matrix[2][3] * Matrix[3][2])
                - Matrix[1][2] * (Matrix[2][1] * Matrix[3][3] - Matrix[2][3] * Matrix[3][1])
                + Matrix[1][3] * (Matrix[2][1] * Matrix[3][2] - Matrix[2][2] * Matrix[3][1]) 
              )
            - Matrix[0][1] *
              (
                  Matrix[1][0] * (Matrix[2][2] * Matrix[3][3] - Matrix[2][3] * Matrix[3][2])
                - Matrix[1][2] * (Matrix[2][0] * Matrix[3][3] - Matrix[2][3] * Matrix[3][0])
                + Matrix[1][3] * (Matrix[2][0] * Matrix[3][2] - Matrix[2][2] * Matrix[3][0])
              )

            + Matrix[0][2] *
              (
                  Matrix[1][0] * (Matrix[2][1] * Matrix[3][3] - Matrix[2][3] * Matrix[3][1])
                - Matrix[1][1] * (Matrix[2][0] * Matrix[3][3] - Matrix[2][3] * Matrix[3][0])
                + Matrix[1][3] * (Matrix[2][0] * Matrix[3][1] - Matrix[2][1] * Matrix[3][0])
              )

            - Matrix[0][3] *
              (
                  Matrix[1][0] * (Matrix[2][1] * Matrix[3][2] - Matrix[2][2] * Matrix[3][1])
                - Matrix[1][1] * (Matrix[2][0] * Matrix[3][2] - Matrix[2][2] * Matrix[3][0])
                + Matrix[1][2] * (Matrix[2][0] * Matrix[3][1] - Matrix[2][1] * Matrix[3][0])
              );
    }

  }
}

#ifdef _MSC_VER
#pragma warning (pop) // (disable : 4459) (disable : 4544) (disable : 4201)
#endif // _MSC_VER

#endif // _ME_CORE_MATH_MATRIX_4X4_