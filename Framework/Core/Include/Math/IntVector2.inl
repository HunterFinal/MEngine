#ifndef _ME_CORE_MATH_INTVECTOR2_INL_
#define _ME_CORE_MATH_INTVECTOR2_INL_

namespace MEngine
{

namespace Math
{

template<typename IntegerType>
Int_Vector_Requirement(IntegerType)
MIntVector2<IntegerType>::MIntVector2<IntegerType>(IN IntegerType InX, IN IntegerType InY)
  : X{InX}
  , Y{InY}
{ }


} // namespace MEngine::Math

} // namespace MEngine


#endif // _ME_CORE_MATH_INTVECTOR2_INL_