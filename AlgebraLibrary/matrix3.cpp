#include "pch.h"
#include "matrix3.h"
#include "vector3.h"
#include "point3.h"
#include "quaternion.h"
#include "axis_angle.h"
#include "euler.h"

Matrix3::Matrix3() : x(Versor3::right()), y(Versor3::up()), z(Versor3::forward()) {}

// constructor that takes as input the coefficient (RAW-MAJOR order!)
Matrix3::Matrix3(
	Scalar m00, Scalar m01, Scalar m02,
	Scalar m10, Scalar m11, Scalar m12,
	Scalar m20, Scalar m21, Scalar m22) 
	: Matrix3()
{
	// TODO M-Constr
	Vector3 _c1(m00, m10, m20), _c2(m01, m11, m21), _c3(m02, m12, m22);
	x = normalize(_c1);
	y = normalize(_c2);
	z = normalize(_c3);
}

Matrix3::Matrix3(Versor3 _x, Versor3 _y, Versor3 _z) : 
x(_x), y(_y), z(_z)
{

}

Vector3 Matrix3::apply(Vector3  v) const {
	// TODO M-App: how to apply a rotation of this type?
	Vector3 res;
	
	if (isRot())
	{
		res.x = v.x * x.x + v.y * y.x + v.z * z.x;
		res.x = v.x * x.y + v.y * y.y + v.z * z.y;
		res.x = v.x * x.z + v.y * y.z + v.z * z.z;
	}

	return res;
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
	return x;
}

Versor3 Matrix3::axisY() const  // TODO M-Ax b
{
	return y;
}

Versor3 Matrix3::axisZ() const  // TODO M-Ax c
{
	return z;
}

// combine two rotations (r goes first!)
Matrix3 Matrix3::operator * (Matrix3 r) const {
	Matrix3 res;
	//1 row
	res.x.x = r.x.x * x.x + r.y.x * x.y + r.z.x * x.z;
	res.y.x = r.x.x * y.x + r.y.x * y.y + r.z.x * y.z;
	res.z.x = r.x.x * z.x + r.y.x * z.y + r.z.x * z.z;
	//2 row
	res.x.y = r.x.y * x.x + r.y.y * x.y + r.z.y * x.z;
	res.y.y = r.x.y * y.x + r.y.y * y.y + r.z.y * y.z;
	res.z.y = r.x.y * z.x + r.y.y * z.y + r.z.y * z.z;
	//3 row
	res.x.z = r.x.z * x.z + r.y.z * x.y + r.z.z * x.z;
	res.y.z = r.x.z * y.z + r.y.z * y.y + r.z.z * y.z;
	res.z.z = r.x.z * z.z + r.y.z * z.y + r.z.z * z.z;

	return res;
}

Matrix3 Matrix3::inverse() const {
	// TODO M-Inv a
	Matrix3 mTemp(x, y, z);
	mTemp.invert();
	return mTemp;
}

void Matrix3::invert() {
	// TODO M-Inv b
	Transpose();
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Matrix3 Matrix3::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO M-LookAt
	Vector3 v = (target - eye) / norm(target - eye);
	Matrix3 rot;
	rot.z = normalize(v);
	rot.x = normalize(cross(Versor3::up(), rot.z) / norm(Versor3::up().asVector() - rot.z.asVector()));
	rot.y = normalize(cross(rot.z, rot.x));

	return rot;
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
	bool IsRot = false;
	IsRot = (Det() - 1.0 < EPSILON);
	IsRot = cross(x, y) == z.asVector();
	IsRot = cross(x, z) == y.asVector();
	IsRot = cross(z, y) == x.asVector();

	return IsRot;
}

// return a rotation matrix around an axis
Matrix3 Matrix3::rotationX(Scalar angleDeg)  // TODO M-Rx
{
	Matrix3 XRot;
	XRot.y.y = cos(angleDeg);
	XRot.y.z = sin(angleDeg);
	XRot.z.y = -sin(angleDeg);
	XRot.z.z = cos(angleDeg);
}

Matrix3 Matrix3::rotationY(Scalar angleDeg)   // TODO M-Ry
{
	Matrix3 YRot;
	YRot.x.x = cos(angleDeg);
	YRot.x.z = -sin(angleDeg);
	YRot.z.x = sin(angleDeg);
	YRot.z.z = cos(angleDeg);
}

Matrix3 Matrix3::rotationZ(Scalar angleDeg)   // TODO M-Rz
{
	Matrix3 ZRot;
	ZRot.x.x = cos(angleDeg);
	ZRot.y.x = -sin(angleDeg);
	ZRot.x.y = sin(angleDeg);
	ZRot.y.x = cos(angleDeg);
}

void Matrix3::printf() const // TODO Print
{
	cout << "| " << x.x << ", " << y.x << ", " << z.x << " |" << endl;
	cout << "| " << x.y << ", " << y.y << ", " << z.y << " |" << endl;
	cout << "| " << x.z << ", " << y.z << ", " << z.z << " |" << endl;
}

Scalar Matrix3::Det() const
{
	/*Scalar detX = x.x * ((y.y * z.z) - (z.y * y.z));
	Scalar detY = y.x * ((x.y * z.z) - (z.y * x.z));
	Scalar detZ = z.x * ((x.y * y.z) - (y.y * x.z));
	return detX - detY + detZ;*/
	return dot(cross(x, y), z.asVector());
}

void Matrix3::Transpose()
{
	Scalar tempX_Y = x.y;
	x.y = y.x;
	y.x = tempX_Y;
	Scalar tempX_Z = x.y;
	x.z = z.x;
	z.x = tempX_Z;
	Scalar tempY_Z = x.y;
	y.z = z.y;
	z.y = tempY_Z;
}
