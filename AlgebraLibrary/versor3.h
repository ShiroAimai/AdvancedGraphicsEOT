#pragma once

#include <math.h>
#include "vector3.h"

using Scalar = double;

class Versor3{
private:
	friend Versor3 normalize(Vector3 p);
	friend Versor3 Vector3::asVersor() const;

    // constructors
    Versor3(Scalar _x, Scalar _y, Scalar _z);
public:
    Scalar x,y,z;

    static Versor3 right()   { return Versor3(+1, 0, 0);} // aka EAST
    static Versor3 left()    { return Versor3(-1, 0, 0);} // aka WEST
    static Versor3 up()      { return Versor3( 0,+1, 0);}
    static Versor3 down()    { return Versor3( 0,-1, 0);}
    static Versor3 forward() { return Versor3( 0, 0,+1);} // aka NORTH
    static Versor3 backward(){ return Versor3( 0, 0,-1);} // aka SOUTH

    // access to the coordinates: to write them
    Scalar& operator[] (int i);

    // access to the coordinates: to read them
    Scalar operator[] (int i) const;

    Vector3 operator*(Scalar k) const;

    Versor3 operator -() const;

    Versor3 operator +() const;

    Vector3 asVector() const;

    void printf() const;// TODO Print

};

inline Versor3 normalize(Vector3 p){
    Scalar n = norm(p);
    return Versor3( p.x/n, p.y/n, p.z/n );
}

// cosine between a and b
inline Scalar dot(const Versor3 &a, const Versor3 &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// lenght of projection of b along a
inline Scalar dot(const Versor3 &a, const Vector3 &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3 cross(const Versor3 &a, const Versor3 &b){
    return Vector3(
                a.y*b.z-a.z*b.y ,
                a.z*b.x-a.x*b.z ,
                a.x*b.y-a.y*b.x );
}


inline Vector3 operator*( Scalar k, const Versor3& a){ return a*k; }

inline Versor3 nlerp( const Versor3& a,const Versor3& b, Scalar t){
    // TODO nlerp
    return Versor3::up();
}

inline Versor3 slerp( const Versor3& a,const Versor3& b, Scalar t){
    // TODO slerp
    return Versor3::up();
}


