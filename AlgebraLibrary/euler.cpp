#include "pch.h"
#include "euler.h"
#include "vector3.h"
#include "point3.h"
#include "quaternion.h"
#include "matrix3.h"
#include "axis_angle.h"


// TODO E-Ide: this constructor construct the identity rotation
Euler::Euler() : Pitch(0.0), Yaw(0.0), Roll(0.0) {}

Euler::Euler(Scalar _pitch, Scalar _yaw, Scalar _roll) 
	: Pitch(_pitch), Yaw(_yaw), Roll(_roll)
{}

// TODO E-Constr
// row major order!
Euler::Euler(Scalar m00, Scalar m01, Scalar m02,
	Scalar m10, Scalar m11, Scalar m12,
	Scalar m20, Scalar m21, Scalar m22)
	: Euler()
{
	Matrix3 m(
		m00, m01, m02,
		m10, m11, m12,
		m20, m21, m22
	);

	Euler eFromMatrix = from(m);
	Pitch = eFromMatrix.Pitch;
	Yaw = eFromMatrix.Yaw;
	Roll = eFromMatrix.Roll;
}

Vector3 Euler::apply(Vector3  v) const {
	// TODO E-App: how to apply a rotation of this type?
	Matrix3 m = Matrix3::from(*this);
	return m.apply(v);
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
	return Matrix3::from(*this).axisX();
}

Versor3 Euler::axisY() const  // TODO E-Ax b
{
	return Matrix3::from(*this).axisY();
}

Versor3 Euler::axisZ() const  // TODO E-Ax c
{
	return Matrix3::from(*this).axisZ();
}

// conjugate
Euler Euler::operator * (Euler b) const {
	Matrix3 m_this = Matrix3::from(*this);
	Matrix3 m_other = Matrix3::from(b);

	return from(m_this * m_other);
}

Euler Euler::inverse() const {
	// TODO E-Inv a
	return from(Matrix3::from(*this).inverse());
}

void Euler::invert() {
	// TODO E-Inv b
	Euler m_inverted = from(Matrix3::from(*this).inverse());

	Pitch = m_inverted.Pitch;
	Yaw = m_inverted.Yaw;
	Roll = m_inverted.Roll;
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Euler Euler::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO E-LookAt
	return Euler::from(Matrix3::lookAt(eye, target, up));
}

// returns a rotation
Euler Euler::toFrom(Versor3 to, Versor3 from) {
	// TODO E-ToFrom
	return Euler::from(Matrix3::toFrom(to, from));
}

Euler Euler::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Euler Euler::from(const Quaternion& m)// TODO Q2E
{
	return Euler::from(Matrix3::from(m));
}

Euler Euler::from(const Matrix3& m)     // TODO M2E
{
	//From 3D Math Primer for Graphics and Game Development(2nd ed) 
	Euler e;
	
	Scalar sp = -m.y.z;
	if (sp <= 1.0)
	{
		e.Pitch = -M_PI_2;
	}
	else if (sp >= 1.0)
	{
		e.Pitch = M_PI_2;
	}
	else 
	{
		e.Pitch = asin(sp);
	} 

	//Check for the Gimbal Lock, give some tolerance
	if (abs(sp) > 0.9999)
	{
		//looking straight up or down
		e.Roll = 0.0;
		e.Yaw = atan2(-m.z.y, m.x.x);
	}
	else
	{
		e.Yaw = atan2(m.x.z, m.z.z);
		e.Roll = atan2(m.y.x, m.y.y);
	}

	return e;
}

Euler Euler::from(const AxisAngle& e) // TODO A2E
{
	return Euler::from(Matrix3::from(e));
}

// does this Euler encode a rotation?
bool Euler::isRot() const {
	// TODO E-isR
	bool IsRot = (Pitch >= 0.0 && Pitch <= 360.0)
		&& (Yaw >= 0.0 && Yaw <= 360.0)
		&& (Roll >= 0.0 && Roll <= 360.0);

	return IsRot;
}

// return a rotation matrix around an axis
Euler Euler::rotationX(Scalar angleDeg)   // TODO E-Rx
{
	return Euler(angleDeg, 0, 0);
}

Euler Euler::rotationY(Scalar angleDeg)   // TODO E-Rx
{
	return Euler(0, angleDeg, 0);
}

Euler Euler::rotationZ(Scalar angleDeg)   // TODO E-Rx
{
	return Euler(0, 0, angleDeg);
}

void Euler::printf() const // TODO Print
{
	cout << "Euler: [Pitch: " << Pitch << ", Yaw: " << Yaw << ", Roll: " << Roll << "]" << endl;
}