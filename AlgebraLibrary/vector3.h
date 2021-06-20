#pragma once
#include <math.h>

typedef double Scalar;

class Point3; // prometto che esiste una classe Point3 da qualche parte
class Versor3;

const Scalar EPSILON = 0.0001;
const Scalar EPSILON2 = EPSILON*EPSILON;

class Vector3{
public:
    Scalar x,y,z;

    // constructors
    Vector3():x(0),y(0),z(0){ }
    Vector3(Scalar _x, Scalar _y, Scalar _z):x(_x),y(_y),z(_z){ }

    static Vector3 right()   { return Vector3(+1, 0, 0);}
    static Vector3 left()    { return Vector3(-1, 0, 0);}
    static Vector3 up()      { return Vector3( 0,+1, 0);}
    static Vector3 down()    { return Vector3( 0,-1, 0);}
    static Vector3 fowrard() { return Vector3( 0, 0,+1);}
    static Vector3 backward(){ return Vector3( 0, 0,-1);}

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

    // vector sum
    Vector3 operator+(const Vector3 &b) const{
        return Vector3( x+b.x, y+b.y, z+b.z );
    }

    // vector-sum: in-place version
    void operator+=(const Vector3 &b) {
        x += b.x;
        y += b.y;
        z += b.z;
    }

    Vector3 operator-(const Vector3 &b) const{
        return Vector3( x-b.x, y-b.y, z-b.z );
    }

    // unitary minus operator
    Vector3 operator-() const {
        return Vector3(-x,-y,-z);
    }

    Vector3 operator*(const Vector3 & b) const{
        return Vector3( b.x*x, b.y*y, b.z*z );
    }

    void operator *= (const Vector3 & b){
        x *= b.x;
        y *= b.y;
        z *= b.z;
    }

    Vector3 operator*(Scalar k) const{
        return Vector3( k*x, k*y, k*z );
    }

    void operator *= (Scalar k){
        x *= k;
        y *= k;
        z *= k;
    }

    Vector3 operator/(Scalar k) const{
        return Vector3( x/k, y/k, z/k );
    }

    void operator /= (Scalar k){
        x /= k;
        y /= k;
        z /= k;
    }

    Point3 asPoint() const;
    Versor3 asVersor() const;

    void printf() const {} // TODO Print
};


inline Scalar dot(const Vector3 &a, const Vector3 &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3 cross(const Vector3 &a, const Vector3 &b){
    return Vector3(
                a.y*b.z-a.z*b.y ,
                a.z*b.x-a.x*b.z ,
                a.x*b.y-a.y*b.x );
}

inline Scalar squaredNorm(const Vector3 &a){
    return  dot(a,a) ;
}

inline Scalar norm(const Vector3 &a){
    return sqrt( squaredNorm(a) );
}


inline Vector3 operator*( Scalar k, const Vector3& a){ return a*k; }

inline Vector3 lerp( const Vector3& a,const Vector3& b, Scalar t){
    return (1-t)*a + t*b;
}


