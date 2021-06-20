#include "pch.h"
#include "vector3.h"
#include "point3.h"
#include "versor3.h"

// constructors
Vector3::Vector3() :x(0), y(0), z(0) { }
Vector3::Vector3(Scalar _x, Scalar _y, Scalar _z) :x(_x), y(_y), z(_z) { }

// access to the coordinates: to write them
Scalar& Vector3::operator[] (int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

// access to the coordinates: to read them
Scalar Vector3::operator[] (int i) const {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

// vector sum
Vector3 Vector3::operator+(const Vector3& b) const {
	return Vector3(x + b.x, y + b.y, z + b.z);
}

// vector-sum: in-place version
void Vector3::operator+=(const Vector3& b) {
	x += b.x;
	y += b.y;
	z += b.z;
}

Vector3 Vector3::operator-(const Vector3& b) const {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

// unitary minus operator
Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const Vector3& b) const {
	return Vector3(b.x * x, b.y * y, b.z * z);
}

void Vector3::operator *= (const Vector3& b) {
	x *= b.x;
	y *= b.y;
	z *= b.z;
}

Vector3 Vector3::operator*(Scalar k) const {
	return Vector3(k * x, k * y, k * z);
}

void Vector3::operator *= (Scalar k) {
	x *= k;
	y *= k;
	z *= k;
}

Vector3 Vector3::operator/(Scalar k) const {
	return Vector3(x / k, y / k, z / k);
}

void Vector3::operator /= (Scalar k) {
	x /= k;
	y /= k;
	z /= k;
}

Point3 Vector3::asPoint() const
{
	return Point3(x, y, z);
}

// under my own resposability, I declare this vector to be unitary and therefore a VERSOR
Versor3 Vector3::asVersor() const {
	// TODO: a nice assert?
	return Versor3(x, y, z);
}

void Vector3::printf() const {} // TODO Print