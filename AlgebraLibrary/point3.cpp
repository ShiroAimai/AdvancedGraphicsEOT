#include "pch.h"
#include "point3.h"


// constructors
Point3::Point3() :x(0), y(0), z(0) { } // origin
Point3::Point3(Scalar _x, Scalar _y, Scalar _z) :x(_x), y(_y), z(_z) { }

Point3 Point3::origin() { return Point3(0, 0, 0); }

// access to the coordinates
Scalar& Point3::operator[] (int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

Scalar Point3::operator[] (int i) const {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

// point + vector = Point
Point3 Point3::operator-(const Vector3& b) const {
	return Point3(x - b.x, y - b.y, z - b.z);
}

// point to point difference
Vector3 Point3::operator-(const Point3& b) const {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

// point plus vector out-of-place
Point3 Point3::operator + (const Vector3& b) const {
	return Point3(x + b.x, y + b.y, z + b.z);
}

// point plus vector in-place
void Point3::operator+=(const Vector3& b) {
	x += b.x;
	y += b.y;
	z += b.z;
}

Point3 Point3::scaled(Scalar k) const {
	return Point3(x * k, y * k, z * k);
}

Vector3 Point3::asVector() const {
	//return *this - origin();

	return Vector3(x, y, z);
}

bool Point3::isEqual(const Point3& b) {
	return squaredNorm(*this - b) < EPSILON2;
}

void Point3::printf() const // TODO Print
{
	cout << "Point3 [x: " << x << ", " << "y: " << y << ", " << "z: " << z << "]" << endl;
}