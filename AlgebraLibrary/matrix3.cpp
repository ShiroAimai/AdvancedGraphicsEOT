#include "pch.h"
#include "matrix3.h"
#include "vector3.h"
#include "point3.h"
#include "quaternion.h"
#include "axis_angle.h"
#include "euler.h"

Matrix3::Matrix3() {}

// constructor that takes as input the coefficient (RAW-MAJOR order!)
Matrix3::Matrix3(Scalar m00, Scalar m01, Scalar m02,
	Scalar m10, Scalar m11, Scalar m12,
	Scalar m20, Scalar m21, Scalar m22) {
	// TODO M-Constr
}

Vector3 Matrix3::apply(Vector3  v) const {
	// TODO M-App: how to apply a rotation of this type?
	return Vector3();
}

// Rotations can be applied to versors or vectors just as well
Versor3 Matrix3::apply(Versor3 dir) const {
	return apply(dir.asVector()).asVersor();
}

Point3 Matrix3::apply(Point3 p) const {
	return apply(p.asVector()).asPoint();
}

// syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
Versor3 Matrix3::operator() (Versor3 p) { return apply(p); }
Point3  Matrix3::operator() (Point3  p) { return apply(p); }
Vector3 Matrix3::operator() (Vector3 p) { return apply(p); }

Versor3 Matrix3::axisX() const  // TODO M-Ax a
{
	return Versor3::forward();
}

Versor3 Matrix3::axisY() const  // TODO M-Ax b
{
	return Versor3::forward();
}

Versor3 Matrix3::axisZ() const  // TODO M-Ax c
{
	return Versor3::forward();
}

// combine two rotations (r goes first!)
Matrix3 Matrix3::operator * (Matrix3 r) const {
	return Matrix3();
}

Matrix3 Matrix3::inverse() const {
	// TODO M-Inv a
	return Matrix3();
}

void Matrix3::invert() const {
	// TODO M-Inv b
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Matrix3 Matrix3::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO M-LookAt
	return Matrix3();
}

// returns a rotation
Matrix3 Matrix3::toFrom(Versor3 to, Versor3 from) {
	// TODO M-ToFrom
	return Matrix3();
}

Matrix3 Matrix3::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Matrix3 Matrix3::from(Quaternion m)// TODO Q2M
{
	return Matrix3();
}

Matrix3 Matrix3::from(Euler e) // TODO E2M
{
	return Matrix3();
}

Matrix3 Matrix3::from(AxisAngle e) // TODO A2M
{
	return Matrix3();
}

// does this Matrix3 encode a rotation?
bool Matrix3::isRot() const {
	// TODO M-isR
	return false;
}

// return a rotation matrix around an axis
Matrix3 Matrix3::rotationX(Scalar angleDeg)  // TODO M-Rx
{
	return Matrix3();
}

Matrix3 Matrix3::rotationY(Scalar angleDeg)   // TODO M-Ry
{
	return Matrix3();
}

Matrix3 Matrix3::rotationZ(Scalar angleDeg)   // TODO M-Rz
{
	return Matrix3();
}

void Matrix3::printf() const {} // TODO Print