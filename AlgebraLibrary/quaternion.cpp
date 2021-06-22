#include "pch.h"
#include "quaternion.h"
#include "vector3.h"
#include "point3.h"
#include "matrix3.h"
#include "euler.h"
#include "axis_angle.h"

// TODO Q-Ide: this constructor construct the identity rotation
Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(1.0) {}

Quaternion::Quaternion(Scalar _x, Scalar _y, Scalar _z, Scalar _w)
	: x(_x), y(_y), z(_z), w(_w)
{

}

Quaternion::Quaternion(Scalar a, Scalar b, Scalar c) : x(a), y(b), z(c), w(0.0) {
	// TODO Q-Constr
}

// TODO Q-FromPoint
// returns a quaternion encoding a point
Quaternion::Quaternion(const Point3& p) : x(p.x), y(p.y), z(p.z), w(0.0) {
	// TODO
}

Vector3 Quaternion::apply(Vector3  v) const {
	// TODO Q-App: how to apply a rotation of this type?
	if (!isRot()) return v;

	Quaternion PointQuat(v.asPoint());
	Quaternion Inverse = inverse();
	Quaternion res = *this * PointQuat * Inverse;

	return Vector3(res.x, res.y, res.z);
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

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	Quaternion res;
	res.x = x + other.x;
	res.y = y + other.y;
	res.z = z + other.z;
	res.w = w + other.w;

	return res;
}

// conjugate
Quaternion Quaternion::operator * (const Quaternion& r) const {
	
	Vector3 m_imm(x, y, z);
	Vector3 r_imm(r.x, r.y, r.z);

	/*Quaternion res;
	res.w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
	res.x = (w * r.x) + (x * r.w) + (y * r.z) - (z * r.y);
	res.y = (w * r.y) - (x * r.z) + (y * r.w) + (z * r.x);
	res.z = (w * r.z) + (x * r.y) - (y * r.x) + (z * r.w);
	return res;*/

	Vector3 v_res = (r.w * m_imm) + (w * r_imm) + cross(m_imm, r_imm);
	Scalar w_res = (w * r.w) - dot(m_imm, r_imm);
	
	return Quaternion(v_res.x, v_res.y, v_res.z, w_res);
}

Quaternion Quaternion::operator*(Scalar scalar) const
{
	Quaternion res(*this);
	res.x *= scalar;
	res.x *= scalar;
	res.x *= scalar;
	res.x *= scalar;

	return res;
}

Quaternion Quaternion::inverse() const {
	// TODO Q-Inv a
	if (isRot())
	{
		return conjugated();
	}
	else
	{
		Quaternion qInverse(*this);
		qInverse.invert();
		return qInverse;
	}
}

void Quaternion::invert() {
	// TODO Q-Inv b
	conjugate();

	if (!isRot())
	{
		Scalar sqrdMagnitude = SquaredMagnitude();
		x /= sqrdMagnitude;
		y /= sqrdMagnitude;
		z /= sqrdMagnitude;
		w /= sqrdMagnitude;
	}
}

// specific methods for quaternions...
Quaternion Quaternion::conjugated() const {
	// TODO Q-Conj a
	Quaternion res(*this);
	res.conjugate();
	return res;
}

void Quaternion::conjugate() {
	// TODO Q-Conj b
	x = -x;
	y = -y;
	z = -z;
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Quaternion Quaternion::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO Q-LookAt
	Versor3 Dir = normalize(target - eye);
	Versor3 rotAxis = normalize(cross(Versor3::forward(), Dir));
	
	Scalar angle = acos(dot(Versor3::forward(), Dir));
	
	return from(AxisAngle(rotAxis, angle));
}

// returns a rotation
Quaternion Quaternion::toFrom(Versor3 to, Versor3 from) {
	// TODO Q-ToFrom
	Quaternion q;
	
	Vector3 axis = cross(from, to);
	q.x = axis.x;
	q.y = axis.y;
	q.z = axis.z;

	q.w = dot(from, to); // sqrt((to.Length ^ 2) * (from.Length ^ 2)) + dot(to, from);

	return normalize(q);
}

Quaternion Quaternion::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Quaternion Quaternion::from(Matrix3 m)   // TODO M2Q
{
	return from(AxisAngle::from(m));
}

Quaternion Quaternion::from(Euler e)     // TODO E2Q
{
	return Quaternion();
}

Quaternion Quaternion::from(AxisAngle e) // TODO A2Q
{
	Scalar halfSin = sin(e.angle / 2.0);
	Vector3 axis = e.axis * halfSin;
	return Quaternion(axis.x, axis.y, axis.z, cos(e.angle / 2.0));
}

// does this quaternion encode a rotation?
bool Quaternion::isRot() const {
	// TODO Q-isR
	Scalar squaredQuatLength = SquaredMagnitude();
	bool IsRot = (squaredQuatLength - 1 <= EPSILON2);
	return IsRot;
}

// does this quaternion encode a poont?
bool Quaternion::isPoint() const {
	// TODO Q-isP
	return (w <= EPSILON);
}

void Quaternion::printf() const // TODO Print
{
	cout << "Q : {[" << x << ", " << y << ", " << z << "], " << w << "}" << endl;
}

Scalar Quaternion::Magnitude() const
{
	return sqrt(SquaredMagnitude());
}

Scalar Quaternion::SquaredMagnitude() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}