#include "pch.h"
#include "euler.h"
#include "vector3.h"
#include "point3.h"
#include "quaternion.h"
#include "matrix3.h"
#include "axis_angle.h"

// TODO E-Ide: this constructor construct the identity rotation
Euler::Euler() {}

// TODO E-Constr
// row major order!
Euler::Euler(Scalar m00, Scalar m01, Scalar m02,
	Scalar m10, Scalar m11, Scalar m12,
	Scalar m20, Scalar m21, Scalar m22)
{
}

Vector3 Euler::apply(Vector3  v) const {
	// TODO E-App: how to apply a rotation of this type?
	return Vector3();
}

// Rotations can be applied to versors or vectors just as well
Versor3 Euler::apply(Versor3 dir) const {
	return apply(dir.asVector()).asVersor();
}

Point3 Euler::apply(Point3 p) const {
	return apply(p.asVector()).asPoint();
}

// syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
Versor3 Euler::operator() (Versor3 p) { return apply(p); }
Point3  Euler::operator() (Point3  p) { return apply(p); }
Vector3 Euler::operator() (Vector3 p) { return apply(p); }

Versor3 Euler::axisX() const  // TODO E-Ax a
{
	return Versor3::forward();
}

Versor3 Euler::axisY() const  // TODO E-Ax b
{
	return Versor3::forward();
}

Versor3 Euler::axisZ() const  // TODO E-Ax c
{
	return Versor3::forward();
}


// conjugate
Euler Euler::operator * (Euler b) const {
	return Euler();
}

Euler Euler::inverse() const {
	// TODO E-Inv a
	return Euler();
}

void Euler::invert() const {
	// TODO E-Inv b
}

// specific methods for Eulers...
Euler Euler::transposed() const {
	// TODO E-Transp a
	return Euler();
}

void Euler::transpose() {
	// TODO E-Transp b
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Euler Euler::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO E-LookAt
	return Euler();
}

// returns a rotation
Euler Euler::toFrom(Versor3 to, Versor3 from) {
	// TODO E-ToFrom
	return Euler();
}

Euler Euler::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Euler Euler::from(Quaternion m)// TODO Q2M
{
	return Euler();
}

Euler Euler::from(Euler e)     // TODO E2M
{
	return Euler();
}

Euler Euler::from(AxisAngle e) // TODO E2M
{
	return Euler();
}

// does this Euler encode a rotation?
bool Euler::isRot() const {
	// TODO E-isR
	return false;
}

// return a rotation matrix around an axis
Euler Euler::rotationX(Scalar angleDeg)   // TODO E-Rx
{
	return Euler();
}

Euler Euler::rotationY(Scalar angleDeg)   // TODO E-Rx
{
	return Euler();
}

Euler Euler::rotationZ(Scalar angleDeg)   // TODO E-Rx
{
	return Euler();
}

void Euler::printf() const {} // TODO Print