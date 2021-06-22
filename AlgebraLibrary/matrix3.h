#pragma once

#include <math.h>
#include "versor3.h"

/* Matrix3 class */
/* this class is a candidate to store a rotation! */
/* as such, it implements all the expected methods    */

class Quaternion;
class AxisAngle;
class Euler;
class Vector3;
class Point3;

class Matrix3{
public:

    /* fields */

    // TODO M-Fields: which fields to store? (also add a constuctor taking these fields).
    Versor3 x, y, z;

    // TODO M-Ide: this constructor construct the identity rotation
    Matrix3();

    // constructor that takes as input the coefficient (RAW-MAJOR order!)
    Matrix3(Scalar m00, Scalar m01, Scalar m02,
        Scalar m10, Scalar m11, Scalar m12,
        Scalar m20, Scalar m21, Scalar m22);

    Matrix3(Versor3 _x, Versor3 _y, Versor3 _z);

    Vector3 apply(Vector3  v) const;

    // Rotations can be applied to versors or vectors just as well
    Versor3 apply(Versor3 dir) const;

    Point3 apply(Point3 p) const;

    // syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
    Versor3 operator() (Versor3 p);
    Point3  operator() (Point3  p);
    Vector3 operator() (Vector3 p);

    Versor3 axisX() const;  // TODO M-Ax a
    Versor3 axisY() const;  // TODO M-Ax b
    Versor3 axisZ() const;  // TODO M-Ax c

    // combine two rotations (r goes first!)
    Matrix3 operator * (Matrix3 r) const;

    Matrix3 inverse() const;

    void invert();

	// specific methods for matrix...
	Matrix3 transposed() const;

	void transpose();

    // returns a rotation to look toward target, if you are in eye, and the up-vector is up
    static Matrix3 lookAt(Point3 eye, Point3 target, Versor3 up = Versor3::up());

    // returns a rotation
    static Matrix3 toFrom(Versor3 to, Versor3 from);

    static Matrix3 toFrom(Vector3 to, Vector3 from);

    // conversions to this representation
    static Matrix3 from( const Quaternion& q );// TODO Q2M
    static Matrix3 from( const Euler& e );     // TODO E2M
    static Matrix3 from( const AxisAngle& e ); // TODO A2M

    // does this Matrix3 encode a rotation?
    bool isRot() const;

    // return a rotation matrix around an axis
    static Matrix3 rotationX( Scalar angleDeg );   // TODO M-Rx
    static Matrix3 rotationY( Scalar angleDeg );   // TODO M-Ry
    static Matrix3 rotationZ( Scalar angleDeg );   // TODO M-Rz

    void printf() const;// TODO Print

    Scalar Det() const;
};


// interpolation of roations
inline Matrix3 directLerp( const Matrix3& a,const Matrix3& b, Scalar t){
    // TODO M-directLerp: how to interpolate Matrix3s
    return Matrix3();
}

inline Matrix3 lerp( const Matrix3& a,const Matrix3& b, Scalar t){
    // TODO M-smartLerp: how to interpolate Matrix3s
    return Matrix3();
}




