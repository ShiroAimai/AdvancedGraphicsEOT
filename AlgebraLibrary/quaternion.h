#pragma once

#include <math.h>
#include "versor3.h"

/* Quaternion class */
/* this class is a candidate to store a rotation! */
/* as such, it implements all expected methods    */

class Vector3;
class Point3;
class Matrix3;
class AxisAngle;
class Euler;

class Quaternion{
public:

    /* fields */
    // TODO Q-Fields: which fields to store? (also add a constuctor taking these fields).

	// TODO Q-Ide: this constructor construct the identity rotation
	Quaternion();
    Quaternion(Scalar a, Scalar b, Scalar c);
	// TODO Q-FromPoint
	// returns a quaternion encoding a point
    Quaternion(const Point3& p);
   
   
    Vector3 apply(Vector3  v) const;

    // Rotations can be applied to versors or vectors just as well
    Versor3 apply(Versor3 dir) const;

    Point3 apply(Point3 p) const;

    // syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
    Versor3 operator() (Versor3 p);
    Point3  operator() (Point3  p);
    Vector3 operator() (Vector3 p);

    Versor3 axisX() const;  // TODO Q-Ax a
    Versor3 axisY() const;  // TODO Q-Ax b
    Versor3 axisZ() const;  // TODO Q-Ax c

    // conjugate
    Quaternion operator * (Quaternion r) const;

    Quaternion inverse() const;

    void invert() const;

    // specific methods for quaternions...
    Quaternion conjugated() const;
    void conjugate();

    // returns a rotation to look toward target, if you are in eye, and the up-vector is up
    static Quaternion lookAt(Point3 eye, Point3 target, Versor3 up = Versor3::up());

    // returns a rotation
    static Quaternion toFrom(Versor3 to, Versor3 from);

    static Quaternion toFrom(Vector3 to, Vector3 from);

    // conversions to this representation
    static Quaternion from( Matrix3 m );   // TODO M2Q
    static Quaternion from( Euler e );     // TODO E2Q
    static Quaternion from( AxisAngle e ); // TODO A2Q

    // does this quaternion encode a rotation?
    bool isRot() const;


    // does this quaternion encode a poont?
    bool isPoint() const;

    void printf() const;// TODO Print
};

// interpolation or roations
inline Quaternion lerp( const Quaternion& a,const Quaternion& b, Scalar t){
    // TODO Q-Lerp: how to interpolate quaternions
    // hints: shortest path! Also, consdider them are 4D unit vectors.
    return Quaternion();
}



