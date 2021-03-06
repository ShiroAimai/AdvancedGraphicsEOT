#include "pch.h"
#include "axis_angle.h"
#include "quaternion.h"
#include "matrix3.h"
#include "euler.h"
#include "vector3.h"
#include "point3.h"

// TODO A-Ide: this constructor construct the identity rotation
AxisAngle::AxisAngle() : axis(Versor3::forward()), angle(0.0)
{}

AxisAngle::AxisAngle(const Versor3& _axis, Scalar _angle) : axis(_axis), angle(_angle)
{}

// TODO A-FromPoint
// returns a AxisAngle encoding a point
AxisAngle::AxisAngle(const Point3& p) : axis(normalize(p.asVector())), angle(0.0) {
	// TODO
}

Vector3 AxisAngle::apply(Vector3  v) const {
	// TODO A-App: how to apply a rotation of this type?
	Quaternion qFromThis = Quaternion::from(*this);
	return qFromThis.apply(v);
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
	return Matrix3::from(*this).axisX();
}

Versor3 AxisAngle::axisY() const  // TODO A-Ax b
{
	return Matrix3::from(*this).axisY();
}

Versor3 AxisAngle::axisZ() const  // TODO A-Ax c
{
	return Matrix3::from(*this).axisZ();
}

// conjugate
AxisAngle AxisAngle::operator * (AxisAngle r) const {
	Quaternion qFromThis = Quaternion::from(*this);
	Quaternion qFromR = Quaternion::from(r);
	Quaternion res = qFromThis * qFromR;
	
	return from(res);
}

AxisAngle AxisAngle::inverse() const {
	// TODO A-Inv a
	AxisAngle res;
	res.invert();
	return res;
}

void AxisAngle::invert() {
	// TODO A-Inv b
	axis = -axis;
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
AxisAngle AxisAngle::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO A-LookAt
	return from(Matrix3::lookAt(eye, target, up));
}

// returns a rotation
AxisAngle AxisAngle::toFrom(Versor3 to, Versor3 from) {
	// TODO A-ToFrom
	Vector3 fromToOrtho = cross(from, to);
	Versor3 rotAxis = normalize(fromToOrtho);
	Scalar cosine = dot(from, to);
	Scalar angleRad = atan2(norm(fromToOrtho), cosine);

	return AxisAngle(rotAxis, angleRad);
}

AxisAngle AxisAngle::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
AxisAngle AxisAngle::from(const Matrix3& m)  // TODO M2A
{
	const Vector3 res = Vector3((m.y.z - m.z.y), (m.z.x - m.x.z), (m.y.x - m.x.y));
	
	AxisAngle axisAngleRes;
	axisAngleRes.angle = acos((m.x.x + m.y.y + m.z.z - 1.0) / 2.0);
	axisAngleRes.axis = normalize(res);

	return axisAngleRes;
}

AxisAngle AxisAngle::from(const Euler& e)    // TODO E2A
{
	return from(Matrix3::from(e));
}

AxisAngle AxisAngle::from(const Quaternion& q)// TODO Q2A
{
	Quaternion val(q);
	if (val.w > 1.0 + EPSILON)
		val = normalize(val);
	
	return AxisAngle(normalize(val.v), 2.0 * acos(val.w));
}

AxisAngle AxisAngle::rotationX(Scalar angleDeg) //TODO A-Rx
{
	return AxisAngle(Versor3::right(), DegToRad(angleDeg));
}

AxisAngle AxisAngle::rotationY(Scalar angleDeg) //TODO A-Ry
{
	return AxisAngle(Versor3::up(), DegToRad(angleDeg));
}

AxisAngle AxisAngle::rotationZ(Scalar angleDeg) //TODO : A-Rz
{
	return AxisAngle(Versor3::forward(), DegToRad(angleDeg));
}

// does this AxisAngle encode a poont?
bool AxisAngle::isPoint() const {
	// TODO A-isP
	return (abs(angle) <= EPSILON);
}

bool AxisAngle::isRot() const
{
	return !isPoint();
}

void AxisAngle::printf() const // TODO Print
{
	cout << "AngleAxis : [{ "; axis.printf(); cout << ", " << angle << "]" << endl;
}