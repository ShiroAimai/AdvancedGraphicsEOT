#include "pch.h"
#include "matrix4.h"

Versor3 Matrix4::apply(Versor3 d) {
	return normalize(d.x * x + d.y * y + d.z * z);
}

Vector3 Matrix4::apply(Vector3 v) {
	return v.x * x + v.y * y + v.z * z;
}

Point3 Matrix4::apply(Point3 p) {
	return o + p.x * x + p.y * y + p.z * z;
}

Matrix4 Matrix4::inverse() const  // out-of-place
{
	return Matrix4();
}

void Matrix4::invert() // in-place
{

}

Matrix4 Matrix4::operator * (const Matrix4& b) {
	return Matrix4();
}

Scalar Matrix4::det() const {
	return dot(cross(x, y), z);
}