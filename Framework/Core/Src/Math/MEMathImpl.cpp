// MEngine Math static variables definitions

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"


// MVector<Type>
template<> const Vector3D Vector3D::ZeroVector(0.0, 0.0, 0.0);
template<> const Vector3D Vector3D::OneVector(1.0, 1.0, 1.0);
template<> const Vector3D Vector3D::RightVector(1.0, 0.0, 0.0);
template<> const Vector3D Vector3D::LeftVector(-1.0, 0.0, 0.0);
template<> const Vector3D Vector3D::UpVector(0.0, 1.0, 0.0);
template<> const Vector3D Vector3D::DownVector(0.0, -1.0, 0.0);
template<> const Vector3D Vector3D::ForwardVector(0.0, 0.0, 1.0);
template<> const Vector3D Vector3D::BackwardVector(0.0, 0.0, -1.0);
template<> const Vector3D Vector3D::XAxisVector(1.0, 0.0, 0.0);
template<> const Vector3D Vector3D::YAxisVector(0.0, 1.0, 0.0);
template<> const Vector3D Vector3D::ZAxisVector(0.0, 0.0, 1.0);

template<> const Vector3 Vector3::ZeroVector(0.0f, 0.0f, 0.0f);
template<> const Vector3 Vector3::OneVector(1.0f, 1.0f, 1.0f);
template<> const Vector3 Vector3::RightVector(1.0f, 0.0f, 0.0f);
template<> const Vector3 Vector3::LeftVector(-1.0f, 0.0f, 0.0f);
template<> const Vector3 Vector3::UpVector(0.0f, 1.0f, 0.0f);
template<> const Vector3 Vector3::DownVector(0.0f, -1.0f, 0.0f);
template<> const Vector3 Vector3::ForwardVector(0.0f, 0.0f, 1.0f);
template<> const Vector3 Vector3::BackwardVector(0.0f, 0.0f, -1.0f);
template<> const Vector3 Vector3::XAxisVector(1.0f, 0.0f, 0.0f);
template<> const Vector3 Vector3::YAxisVector(0.0f, 1.0f, 0.0f);
template<> const Vector3 Vector3::ZAxisVector(0.0f, 0.0f, 1.0f);

// MVector2D<Type>
template<> const Vector2D Vector2D::ZeroVector(0.0, 0.0);
template<> const Vector2D Vector2D::OneVector(1.0, 1.0);
template<> const Vector2D Vector2D::RightVector(1.0, 0.0);
template<> const Vector2D Vector2D::LeftVector(-1.0, 0.0);
template<> const Vector2D Vector2D::UpVector(0.0, 1.0);
template<> const Vector2D Vector2D::DownVector(0.0, -1.0);
template<> const Vector2D Vector2D::XAxisVector(1.0, 0.0);
template<> const Vector2D Vector2D::YAxisVector(0.0, 1.0);

template<> const Vector2 Vector2::ZeroVector(0.0f, 0.0f);
template<> const Vector2 Vector2::OneVector(1.0f, 1.0f);
template<> const Vector2 Vector2::RightVector(1.0f, 0.0f);
template<> const Vector2 Vector2::LeftVector(-1.0f, 0.0f);
template<> const Vector2 Vector2::UpVector(0.0f, 1.0f);
template<> const Vector2 Vector2::DownVector(0.0f, -1.0f);
template<> const Vector2 Vector2::XAxisVector(1.0f, 0.0f);
template<> const Vector2 Vector2::YAxisVector(0.0f, 1.0f);

// MVector4<Type, AlignSize>
template<> const Vector4D Vector4D::ZeroVector(0.0, 0.0, 0.0, 0.0);
template<> const Vector4D Vector4D::OneVector(1.0, 1.0, 1.0, 1.0);

template<> const Vector4 Vector4::ZeroVector(0.0f, 0.0f, 0.0f, 0.0f);
template<> const Vector4 Vector4::OneVector(1.0f, 1.0f, 1.0f, 1.0f);

// MMatrix4x4<Type, AlignSize>
template<> const Matrix44D Matrix44D::Identity( Vector4D{1.0, 0.0, 0.0, 0.0},
                                                Vector4D{0.0, 1.0, 0.0, 0.0},
                                                Vector4D{0.0, 0.0, 1.0, 0.0},
                                                Vector4D{0.0, 0.0, 0.0, 1.0});

template<> const Matrix44 Matrix44::Identity( Vector4{1.0f, 0.0f, 0.0f, 0.0f},
                                              Vector4{0.0f, 1.0f, 0.0f, 0.0f},
                                              Vector4{0.0f, 0.0f, 1.0f, 0.0f},
                                              Vector4{0.0f, 0.0f, 0.0f, 1.0f});