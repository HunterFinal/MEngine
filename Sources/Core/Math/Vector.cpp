// MEngine Vector static variables definitions

#include "Vector.h"

template<> const Vector3 Vector3::ZeroVector(0.0, 0.0, 0.0);
template<> const Vector3 Vector3::OneVector(1.0, 1.0, 1.0);
template<> const Vector3 Vector3::RightVector(1.0, 0.0, 0.0);
template<> const Vector3 Vector3::LeftVector(-1.0, 0.0, 0.0);
template<> const Vector3 Vector3::UpVector(0.0, 1.0, 0.0);
template<> const Vector3 Vector3::DownVector(0.0, -1.0, 0.0);
template<> const Vector3 Vector3::ForwardVector(0.0, 0.0, 1.0);
template<> const Vector3 Vector3::BackwardVector(0.0, 0.0, -1.0);
template<> const Vector3 Vector3::XAxisVector(1.0, 0.0, 0.0);
template<> const Vector3 Vector3::YAxisVector(0.0, 1.0, 0.0);
template<> const Vector3 Vector3::ZAxisVector(0.0, 0.0, 1.0);

template<> const Vector3f Vector3f::ZeroVector(0.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::OneVector(1.0f, 1.0f, 1.0f);
template<> const Vector3f Vector3f::RightVector(1.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::LeftVector(-1.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::UpVector(0.0f, 1.0f, 0.0f);
template<> const Vector3f Vector3f::DownVector(0.0f, -1.0f, 0.0f);
template<> const Vector3f Vector3f::ForwardVector(0.0f, 0.0f, 1.0f);
template<> const Vector3f Vector3f::BackwardVector(0.0f, 0.0f, -1.0f);
template<> const Vector3f Vector3f::XAxisVector(1.0f, 0.0f, 0.0f);
template<> const Vector3f Vector3f::YAxisVector(0.0f, 1.0f, 0.0f);
template<> const Vector3f Vector3f::ZAxisVector(0.0f, 0.0f, 1.0f);