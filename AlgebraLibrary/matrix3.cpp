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
{}

Vector3 Matrix3::apply(Vector3  v) const {
	// TODO M-App: how to apply a rotation of this type?
	Vector3 res;

	res.x = v.x * x.x + v.y * y.x + v.z * z.x;
	res.y = v.x * x.y + v.y * y.y + v.z * z.y;
	res.z = v.x * x.z + v.y * y.z + v.z * z.z;

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
Matrix3 Matrix3::operator * (const Matrix3& r) const {
	Matrix3 res;
	
	//1 row
	res.x.x = x.x * r.x.x + y.x * r.x.y + z.x * r.x.z;
	res.y.x = x.x * r.y.x + y.x * r.y.y + z.x * r.y.z;
	res.z.x = x.x * r.z.x + y.x * r.z.y + z.x * r.z.z;
	//2 row
	res.x.y = x.y * r.x.x + y.y * r.x.y + z.y * r.x.z;
	res.y.y = x.y * r.y.x + y.y * r.y.y + z.y * r.y.z;
	res.z.y = x.y * r.z.x + y.y * r.z.y + z.y * r.z.z;
	//3 row
	res.x.z = x.z * r.x.z + y.z * r.x.y + z.z * r.x.z;
	res.y.z = x.z * r.y.z + y.z * r.y.y + z.z * r.y.z;
	res.z.z = x.z * r.z.z + y.z * r.z.y + z.z * r.z.z;
	return res;
}

Matrix3 Matrix3::inverse() const {
	// TODO M-Inv a
	return transposed();
}

void Matrix3::invert() {
	// TODO M-Inv b
	transpose();
}

// returns a rotation to look toward target, if you are in eye, and the up-vector is up
Matrix3 Matrix3::lookAt(Point3 eye, Point3 target, Versor3 up) {
	// TODO M-LookAt
	Versor3 v = normalize(target - eye);
	Matrix3 rot;
	rot.z = v;
	rot.x = normalize(cross(up, rot.z));
	rot.y = normalize(cross(rot.z, rot.x));

	return rot;
}

// returns a rotation
Matrix3 Matrix3::toFrom(Versor3 to, Versor3 from) {
	// TODO M-ToFrom
	Versor3 rotAxis = normalize(cross(from, to));
	Scalar cosine = dot(from, to);
	Scalar angleRad = acos(cosine);
	
	AxisAngle _axisAngle(rotAxis, angleRad);
	
	return Matrix3::from(_axisAngle);
}

Matrix3 Matrix3::toFrom(Vector3 to, Vector3 from) {
	return toFrom(normalize(to), normalize(from));
}

// conversions to this representation
Matrix3 Matrix3::from(const Quaternion& q)// TODO Q2M
{
	Matrix3 m;
	
	m.x.x = 1.0 - 2.0 * (q.v.y * q.v.y) - 2.0 * (q.v.z * q.v.z);
	m.x.y = 2.0 * (q.v.x * q.v.y) - 2.0 * (q.w * q.v.z);
	m.x.z = 2.0 * (q.v.x * q.v.z) + 2.0 * (q.w * q.v.y);

	m.y.x = 2.0 * (q.v.x * q.v.y) + 2.0 * (q.w * q.v.z);
	m.y.y = 1.0 - 2.0 * (q.v.x * q.v.x) - 2.0 * (q.v.z * q.v.z);
	m.y.z = 2.0 * (q.v.y * q.v.z) - 2.0 * (q.w * q.v.x);
	 
	m.z.x = 2.0 * (q.v.x * q.v.z) - 2.0 * (q.w * q.v.y);
	m.z.y = 2.0 * (q.v.y * q.v.z) + 2.0 * (q.w * q.v.x);
	m.z.z = 1.0 - 2.0 * (q.v.x * q.v.x) - 2.0 * (q.v.y * q.v.y);

	return m;
}

Matrix3 Matrix3::from(const Euler& e) // TODO E2M
{
	const Matrix3 rotX = rotationX(e.Pitch);
	const Matrix3 rotY = rotationY(e.Yaw);
	const Matrix3 rotZ = rotationZ(e.Roll);

	return rotZ * (rotX * rotY);//zxy
}

Matrix3 Matrix3::from(const AxisAngle& e) // TODO A2M
{
	Matrix3 m;
	Scalar m_cos = cos(e.angle);
	Scalar m_sin = sin(e.angle);
	Scalar offset = 1.0 - m_cos;

	m.x.x = m_cos + (e.axis.x * e.axis.x * offset);
	m.y.y = m_cos + (e.axis.y * e.axis.y * offset);
	m.z.z = m_cos + (e.axis.z * e.axis.z * offset);

	Scalar tmp_1 = e.axis.x * e.axis.y * offset;
	Scalar tmp_2 = e.axis.z * m_sin;
	m.x.y = tmp_1 + tmp_2;
	m.y.x = tmp_1 - tmp_2;

	tmp_1 = e.axis.x * e.axis.z * offset;
	tmp_2 = e.axis.y * m_sin;
	m.x.z = tmp_1 - tmp_2;
	m.z.x = tmp_1 + tmp_2;

	tmp_1 = e.axis.y * e.axis.z * offset;
	tmp_2 = e.axis.x * m_sin;
	m.y.z = tmp_1 + tmp_2;
	m.z.y = tmp_1 - tmp_2;

	return m;
}

// does this Matrix3 encode a rotation?
bool Matrix3::isRot() const {
	// TODO M-isR
	bool IsRot = (abs(Det() - 1.0) < EPSILON)
		&& cross(x, y).IsEqual(z.asVector())
		&& cross(z, x).IsEqual(y.asVector())
		&& cross(y, z).IsEqual(x.asVector());

	return IsRot;
}

// return a rotation matrix around an axis
Matrix3 Matrix3::rotationX(Scalar angleDeg)  // TODO M-Rx
{
	Scalar angleRad = DegToRad(angleDeg);
	Matrix3 XRot;
	XRot.y.y = cos(angleRad);
	XRot.y.z = sin(angleRad);
	XRot.z.y = -sin(angleRad);
	XRot.z.z = cos(angleRad);

	return XRot;
}

Matrix3 Matrix3::rotationY(Scalar angleDeg)   // TODO M-Ry
{
	Scalar angleRad = DegToRad(angleDeg);
	Matrix3 YRot;
	YRot.x.x = cos(angleRad);
	YRot.x.z = -sin(angleRad);
	YRot.z.x = sin(angleRad);
	YRot.z.z = cos(angleRad);

	return YRot;
}

Matrix3 Matrix3::rotationZ(Scalar angleDeg)   // TODO M-Rz
{
	Scalar angleRad = DegToRad(angleDeg);
	Matrix3 ZRot;
	ZRot.x.x = cos(angleRad);
	ZRot.y.x = -sin(angleRad);
	ZRot.x.y = sin(angleRad);
	ZRot.y.y = cos(angleRad);

	return ZRot;
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

Matrix3 Matrix3::transposed() const //TODO : M-trans a
{
	Matrix3 copy(x, y, z);
	copy.transpose();
	return copy;
}

void Matrix3::transpose() //TODO : M-trans b
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
