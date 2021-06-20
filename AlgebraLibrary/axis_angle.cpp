#include "pch.h"
#include "axis_angle.h"
#include "quaternion.h"
#include "matrix3.h"
#include "euler.h"
#include "vector3.h"
#include "point3.h"

// TODO A-Ide: this constructor construct the identity rotation
AxisAngle::AxisAngle() {}

// TODO A-FromPoint
// returns a AxisAngle encoding a point
AxisAngle::AxisAngle(const Point3& p) {
	// TODO
}

Vector3 AxisAngle::apply(Vector3  v) const {
	// TODO A-App: how to apply a rotation of this type?
	return Vector3();
}

// Rotations can be applied to versors or vectors just as well
Versor3 AxisAngle::apply(Versor3 dir) const {
	return apply(dir.asVector()).asVersor();
}

Point3 AxisAngle::apply(Point3 p) const {
	return apply(p.asVector()).asPoint();
}

// syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
Versor3 AxisAngle::operator() (Versor3 p) { return apply(p); }
Point3  AxisAngle::operator() (Point3  p) { return apply(p); }
Vector3 AxisAngle::operator() (Vector3 p) { return apply(p); }

Versor3 AxisAngle::axisX() const  // TODO A-Ax a
{
	return Versor3::forward();
}

Versor3 AxisAngle::axisY() const  // TODO A-Ax b
{
	return Versor3::forward();
}

Versor3 AxisAngle::axisZ() const  // TODO A-Ax c
{
	return Versor3::forward();
}

// conjugate
AxisAngle AxisAngle::operator * (AxisAngle r) const {
	return AxisAngle();
}

AxisAngle AxisAngle::inverse() const {
	// TODO A-Inv a
	return AxisAngle();
}

void AxisAngle::invert() const {
	// TODO A-Inv b
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
AxisAngle AxisAngle::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO A-LookAt
	return AxisAngle();
}

// returns a rotation
AxisAngle AxisAngle::toFrom(Versor3 to, Versor3 from) {
	// TODO A-ToFrom
	return AxisAngle();
}

AxisAngle AxisAngle::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
AxisAngle AxisAngle::from(Matrix3 m)  // TODO M2A
{
	return AxisAngle();
}

AxisAngle AxisAngle::from(Euler e)    // TODO E2A
{
	return AxisAngle();
}

AxisAngle AxisAngle::from(Quaternion q)// TODO Q2A
{
	return AxisAngle();
}

// does this AxisAngle encode a poont?
bool AxisAngle::isPoint() const {
	// TODO A-isP
	return false;
}

void AxisAngle::printf() const {} // TODO Print