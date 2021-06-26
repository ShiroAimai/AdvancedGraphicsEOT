#pragma once

#include "vector3.h"
#include "point3.h"
#include "versor3.h"
#include "quaternion.h"
#include "axis_angle.h"
#include "matrix3.h"
#include "euler.h"

// The BIG CHOICE:
typedef Quaternion Rotation;
//typedef AxisAngle Rotation;
//typedef Matrix3 Rotation;
//typedef Euler Rotation;

class Transform
{
public:
	Scalar   scale;   // scaling (isotropic)
	Rotation rotation; // rotation
	Vector3  translation;  // translation

	// constructor: is the ide
	Transform();

	// description of the local frame!
	Point3 origin() const;
	Versor3 left() const;
	Versor3 right()const;
	Versor3 up() const;
	Versor3 down()const;
	Versor3 forward() const;
	Versor3 backward()const;

	Versor3 apply(Versor3 dir);

	Vector3 apply(Vector3 v);

	Point3 apply(Point3 p);

	// inverse out-of-place
	Transform inverse() const;


	void invert(); // TODO T-invert  (in-place)

	// CUMULATE: first b, then *this
	Transform operator * (const Transform& b);

	// fills a column-major Scalar 4x4 zmatrix for DirectX (or OpenGL)
	// vector d is already allocated
	void fillDirectXMatrix(Scalar d[]);

	// places this transform in the given origin, looking (Z-axis) toward target, given the up vector
	void place(Point3 inputPoint, Point3 target, Versor3 up);

	void printf() const; // TODO
};

inline Transform lerp(const Transform& a, const Transform& b, float t) {
	// TODO: T-lerp

	Transform res;
	res.scale = ((1 - t) * a.scale) + t * b.scale;
	res.rotation = lerp(a.rotation, b.rotation, t);
	res.translation = lerp(a.translation, b.translation, t);

	return res;
}

