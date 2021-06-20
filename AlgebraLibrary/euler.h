#pragma once

#include <math.h>
#include "versor3.h"

/* Euler class */
/* this class is a candidate to store a rotation! */
/* as such, it implements all the expected methods    */

class Quaternion;
class AxisAngle;
class Euler;

class Euler{
public:

    /* fields */
    // TODO E-Fields: which fields to store? (also add a constuctor taking these fields).


    // TODO E-Ide: this constructor construct the identity rotation
    Euler();

    // TODO E-Constr
    // row major order!
    Euler(Scalar m00, Scalar m01, Scalar m02,
        Scalar m10, Scalar m11, Scalar m12,
        Scalar m20, Scalar m21, Scalar m22);

    Vector3 apply(Vector3  v) const;

    // Rotations can be applied to versors or vectors just as well
    Versor3 apply(Versor3 dir) const;

    Point3 apply(Point3 p) const;

    // syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
    Versor3 operator() (Versor3 p);
    Point3  operator() (Point3  p);
    Vector3 operator() (Vector3 p);

    Versor3 axisX() const;  // TODO E-Ax a
    Versor3 axisY() const;  // TODO E-Ax b
    Versor3 axisZ() const;  // TODO E-Ax c

    // conjugate
    Euler operator * (Euler b) const;

    Euler inverse() const;

    void invert() const;

    // specific methods for Eulers...
    Euler transposed() const;

    void transpose();

    // returns a rotation to look toward target, if you are in eye, and the up-vector is up
    static Euler lookAt(Point3 eye, Point3 target, Versor3 up = Versor3::up());

    // returns a rotation
    static Euler toFrom(Versor3 to, Versor3 from);

    static Euler toFrom(Vector3 to, Vector3 from);

    // conversions to this representation
    static Euler from( Quaternion m );// TODO Q2M
    static Euler from( Euler e );     // TODO E2M
    static Euler from( AxisAngle e ); // TODO E2M

    // does this Euler encode a rotation?
    bool isRot() const;

    // return a rotation matrix around an axis
    static Euler rotationX( Scalar angleDeg );   // TODO E-Rx
    static Euler rotationY( Scalar angleDeg );   // TODO E-Rx
    static Euler rotationZ( Scalar angleDeg );   // TODO E-Rx

    void printf() const;// TODO Print
};


// interpolation or roations
inline Euler directLerp( const Euler& a,const Euler& b, Scalar t){
    // TODO E-directLerp: how to interpolate Eulers
    return Euler();
}

inline Euler lerp( const Euler& a,const Euler& b, Scalar t){
    // TODO E-smartLerp: how to interpolate Eulers
    return Euler();
}


