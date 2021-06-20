#include "pch.h"
#include "versor3.h"

Versor3::Versor3(Scalar _x, Scalar _y, Scalar _z) :x(_x), y(_y), z(_z)
{
}

Scalar& Versor3::operator[] (int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

Scalar Versor3::operator[] (int i) const {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	//assert(0);
	return x;
}

Vector3 Versor3::operator*(Scalar k) const {
	return Vector3(k * x, k * y, k * z);
}

Versor3 Versor3::operator -() const {
	return Versor3(-x, -y, -z);
}
Versor3 Versor3::operator +() const {
	return Versor3(x, y, z);
}

Vector3 Versor3::asVector() const {
	//return *this * 1;
	return Vector3(x, y, z);
}

void Versor3::printf() const  // TODO Print
{ 
	cout << "Versor3 [x: " << x << ", " << "y: " << y << ", " << "z: " << z << "]" << endl;
}
