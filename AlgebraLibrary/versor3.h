#pragma once
#include <math.h>
#include "vector3.h"

typedef double Scalar;

class Versor3{
    // constructors
    Versor3(Scalar _x, Scalar _y, Scalar _z):x(_x),y(_y),z(_z){ }
public:
    Scalar x,y,z;

    static Versor3 right()   { return Versor3(+1, 0, 0);} // aka EAST
    static Versor3 left()    { return Versor3(-1, 0, 0);} // aka WEST
    static Versor3 up()      { return Versor3( 0,+1, 0);}
    static Versor3 down()    { return Versor3( 0,-1, 0);}
    static Versor3 fowrard() { return Versor3( 0, 0,+1);} // aka NORTH
    static Versor3 backward(){ return Versor3( 0, 0,-1);} // aka SOUTH

    // access to the coordinates: to write them
    Scalar& operator[] (int i){
        if (i==0) return x;
        if (i==1) return y;
        if (i==2) return z;
        //assert(0);
        return x;
    }

    // access to the coordinates: to read them
    Scalar operator[] (int i) const{
        if (i==0) return x;
        if (i==1) return y;
        if (i==2) return z;
        //assert(0);
        return x;
    }

    Vector3 operator*(Scalar k) const{
        return Vector3( k*x, k*y, k*z );
    }

    Versor3 operator -() const{
        return Versor3( -x, -y, -z );
    }
    Versor3 operator +() const{
        return Versor3( x, y, z );
    }

    friend Versor3 normalize(Vector3 p);
    friend Versor3 Vector3::asVersor() const;

    Vector3 asVector() const{
        //return *this * 1;
        return Vector3(x,y,z);
    }

    void printf() const {} // TODO Print

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

// under my own resposability, I declare this vector to be unitary and therefore a VERSOR
inline Versor3 Vector3::asVersor() const{
    // TODO: a nice assert?
    return Versor3(x,y,z);
}


