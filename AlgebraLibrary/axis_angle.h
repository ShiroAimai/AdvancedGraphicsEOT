#pragma once

#include <math.h>
#include "versor3.h"

/* AxisAngle class */
/* this class is a candidate to store a rotation! */
/* as such, it implements all expected methods    */

class Matrix3;
class Quaternion;
class Euler;

class AxisAngle{
public:

    /* fields */
    // TODO A-Field: which fields to store? (also add a constuctor taking these fields).
    Versor3 axis;
    Scalar angle;

    // TODO A-Ide: this constructor construct the identity rotation
    AxisAngle();
    AxisAngle(const Versor3& _axis, Scalar _angle);
    // TODO A-FromPoint
    // returns a AxisAngle encoding a point
    AxisAngle(const Point3& p);

    Vector3 apply(Vector3  v) const;

    // Rotations can be applied to versors or vectors just as well
    Versor3 apply(Versor3 dir) const;

    Point3 apply(Point3 p) const;

    // syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
    Versor3 operator() (Versor3 p);
    Point3  operator() (Point3  p);
    Vector3 operator() (Vector3 p);

    Versor3 axisX() const;  // TODO A-Ax a
    Versor3 axisY() const;  // TODO A-Ax b
    Versor3 axisZ() const;  // TODO A-Ax c

    // conjugate
    AxisAngle operator * (AxisAngle r) const;
    
    AxisAngle inverse() const;
    void invert();

    // returns a rotation to look toward target, if you are in eye, and the up-vector is up
    static AxisAngle lookAt(Point3 eye, Point3 target, Versor3 up = Versor3::up());

    // returns a rotation
    static AxisAngle toFrom(Versor3 to, Versor3 from);

    static AxisAngle toFrom(Vector3 to, Vector3 from);

    // conversions to this representation
    static AxisAngle from( const Matrix3& m );   // TODO M2A
    static AxisAngle from( const Euler& e );     // TODO E2A
    static AxisAngle from( const Quaternion& q );// TODO Q2A

    // does this AxisAngle encode a poont?
    bool isPoint() const;

    void printf() const; // TODO Print
};


// interpolation or roations
inline AxisAngle lerp( const AxisAngle& a,const AxisAngle& b, Scalar t){
    // TODO A-Lerp: how to interpolate AxisAngles
    // hints: shortest path! Also, consdider them are 4D unit vectors.
    //https://math.stackexchange.com/questions/3414142/most-efficient-way-to-linearly-interpolate-rotations-expressed-as-axis-angles
    const Vector3 aVec = a.axis * a.angle;
    const Vector3 bVec = b.axis * b.angle;

    const Vector3 res = lerp(aVec, bVec, t);

    return AxisAngle(normalize(res), norm(res));
}





