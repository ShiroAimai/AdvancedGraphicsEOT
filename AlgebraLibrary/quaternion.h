#pragma once

#include <math.h>
#include "vector3.h"
#include "point3.h"
#include "versor3.h"

/* Quaternion class */
/* this class is a candidate to store a rotation! */
/* as such, it implements all expected methods    */

class Matrix3;
class AxisAngle;
class Euler;

class Quaternion{
public:

    /* fields */
    // TODO Q-Fields: which fields to store? (also add a constuctor taking these fields).


    Quaternion(Scalar a, Scalar b, Scalar c){
        // TODO Q-Constr
    }

    // TODO Q-Ide: this constructor construct the identity rotation
    Quaternion(){}

    // TODO Q-FromPoint
    // returns a quaternion encoding a point
    Quaternion( const Point3& p){
        // TODO
    }

    Vector3 apply( Vector3  v) const {
        // TODO Q-App: how to apply a rotation of this type?
        return Vector3();
    }

    // Rotations can be applied to versors or vectors just as well
    Versor3 apply( Versor3 dir ) const {
        return apply( dir.asVector() ).asVersor();
    }

    Point3 apply( Point3 p ) const {
        return apply( p.asVector() ).asPoint();
    }

    // syntactic sugar: "R( p )" as a synomim of "R.apply( p )"
    Versor3 operator() (Versor3 p) { return apply(p); }
    Point3  operator() (Point3  p) { return apply(p); }
    Vector3 operator() (Vector3 p) { return apply(p); }

    Versor3 axisX() const;  // TODO Q-Ax a
    Versor3 axisY() const;  // TODO Q-Ax b
    Versor3 axisZ() const;  // TODO Q-Ax c

    // conjugate
    Quaternion operator * (Quaternion r) const {
        return Quaternion();
    }

    Quaternion inverse() const{
        // TODO Q-Inv a
        return Quaternion();
    }

    void invert() const{
        // TODO Q-Inv b
    }

    // specific methods for quaternions...
    Quaternion conjugated() const{
        // TODO Q-Conj a
        return Quaternion();
    }

    void conjugate(){
        // TODO Q-Conj b
    }

    // returns a rotation to look toward target, if you are in eye, and the up-vector is up
    static Quaternion lookAt( Point3 eye, Point3 target, Versor3 up = Versor3::up() ){
        // TODO Q-LookAt
        return Quaternion();
    }

    // returns a rotation
    static Quaternion toFrom( Versor3 to, Versor3 from ){
        // TODO Q-ToFrom
        return Quaternion();
    }

    static Quaternion toFrom( Vector3 to, Vector3 from ){
        return toFrom( normalize(to) , normalize(from) );
    }

    // conversions to this representation
    static Quaternion from( Matrix3 m );   // TODO M2Q
    static Quaternion from( Euler e );     // TODO E2Q
    static Quaternion from( AxisAngle e ); // TODO A2Q

    // does this quaternion encode a rotation?
    bool isRot() const{
        // TODO Q-isR
        return false;
    }


    // does this quaternion encode a poont?
    bool isPoint() const{
        // TODO Q-isP
        return false;
    }

    void printf() const {} // TODO Print
};


// interpolation or roations
inline Quaternion lerp( const Quaternion& a,const Quaternion& b, Scalar t){
    // TODO Q-Lerp: how to interpolate quaternions
    // hints: shortest path! Also, consdider them are 4D unit vectors.
    return Quaternion();
}



