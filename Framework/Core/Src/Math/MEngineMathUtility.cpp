#include "Math/MEngineMathUtility.h"

/**
 * static const for compiler that is not supporting C++17
 */
#if !HAS_CPP_17
namespace MEngine
{
  namespace Math
  {
    const float MMath::PI =                          (3.1415926535897932384626433832795f);
    const float MMath::FLOAT_TOLERANCE_SMALL =       (1.e-8f);
    const float MMath::FLOAT_TOLERANCE_KINDA_SMALL = (1.e-4f);
    const float MMath::BIG_NUMBER =                  (3.4e+38f);
    const float MMath::EULERS_NUMBER =               (2.71828182845904523536f);
    const float MMath::MAX_FLOAT =                   (3.402823466e+38f); // same as FLT_MAX in float.h
    const float MMath::RAD_2_DEG =                   (57.29577951308233f);
    const float MMath::DEG_2_RAD =                   (0.0174532925199433f);

    const double MMath::DOUBLE_PI =                    (3.1415926535897932384626433832795);
    const double MMath::DOUBLE_TOLERANCE_SMALL =       (1.e-8);
    const double MMath::DOUBLE_TOLERANCE_KINDA_SMALL = (1.e-4);
    const double MMath::DOUBLE_BIG_NUMBER =            (3.4e+38);
    const double MMath::DOUBLE_EULERS_NUMBER =         (2.71828182845904523536);
    const double MMath::MAX_DOUBLE =                   (1.7976931348623158e+308); // same as DBL_MAX in float.h
    const double MMath::DOUBLE_RAD_2_DEG =             (57.29577951308233);
    const double MMath::DOUBLE_DEG_2_RAD =             (0.0174532925199433);

    const float MMath::VECTOR_NORMALIZED_THRESHOLD =   (0.001f)
  }
}
#endif