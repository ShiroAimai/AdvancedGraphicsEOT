#include "pch.h"
#include "quaternion.h"
#include "vector3.h"
#include "point3.h"
#include "matrix3.h"
#include "euler.h"
#include "axis_angle.h"

// TODO Q-Ide: this constructor construct the identity rotation
Quaternion::Quaternion() {}

Quaternion::Quaternion(Scalar a, Scalar b, Scalar c) {
	// TODO Q-Constr
}

// TODO Q-FromPoint
// returns a quaternion encoding a point
Quaternion::Quaternion(const Point3& p) {
	// TODO
}

Vector3 Quaternion::apply(Vector3  v) const {
	// TODO Q-App: how to apply a rotation of this type?
	return Vector3();
}

// Rotations can be applied to versors or vectors just as well
Versor3 Quaternion::apply(Versor3 dir) const {
	return apply(dir.asVector()).asVersor();
}

Point3 Quaternion::apply(Point3 p) const {
	return apply(p.asVector()).asPoint();
}

// syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
Versor3 Quaternion::operator() (Versor3 p) { return apply(p); }
Point3  Quaternion::operator() (Point3  p) { return apply(p); }
Vector3 Quaternion::operator() (Vector3 p) { return apply(p); }

Versor3 Quaternion::axisX() const // TODO Q-Ax a
{
	return Versor3::right();
}

Versor3 Quaternion::axisY() const  // TODO Q-Ax b
{
	return Versor3::right();
}

Versor3 Quaternion::axisZ() const  // TODO Q-Ax c
{
	return Versor3::right();
}

// conjugate
Quaternion Quaternion::operator * (Quaternion r) const {
	return Quaternion();
}

Quaternion Quaternion::inverse() const {
	// TODO Q-Inv a
	return Quaternion();
}

void Quaternion::invert() const {
	// TODO Q-Inv b
}

// specific methods for quaternions...
Quaternion Quaternion::conjugated() const {
	// TODO Q-Conj a
	return Quaternion();
}

void Quaternion::conjugate() {
	// TODO Q-Conj b
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Quaternion Quaternion::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO Q-LookAt
	return Quaternion();
}

// returns a rotation
Quaternion Quaternion::toFrom(Versor3 to, Versor3 from) {
	// TODO Q-ToFrom
	return Quaternion();
}

Quaternion Quaternion::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Quaternion Quaternion::from(Matrix3 m)   // TODO M2Q
{
	return Quaternion();
}

Quaternion Quaternion::from(Euler e)     // TODO E2Q
{
	return Quaternion();
}

Quaternion Quaternion::from(AxisAngle e) // TODO A2Q
{
	return Quaternion();
}

// does this quaternion encode a rotation?
bool Quaternion::isRot() const {
	// TODO Q-isR
	return false;
}


// does this quaternion encode a poont?
bool Quaternion::isPoint() const {
	// TODO Q-isP
	return false;
}

void Quaternion::printf() const {} // TODO Print