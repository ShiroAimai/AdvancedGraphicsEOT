#pragma once
#include "vector3.h"

class Vector3;

using Scalar = double;

class Point3{
public:
    Scalar x,y,z;

    // constructors
    Point3(); // origin
    Point3(Scalar _x, Scalar _y, Scalar _z);

    static Point3 origin();

    // access to the coordinates
    Scalar& operator[] (int i);

    Scalar operator[] (int i) const;

    // point + vector = Point
    Point3 operator-(const Vector3& b) const;

    // point to point difference
    Vector3 operator-(const Point3& b) const;

    // point plus vector out-of-place
    Point3 operator + (const Vector3& b) const;

    // point plus vector in-place
    void operator+=(const Vector3& b);

    Point3 scaled(Scalar k) const;

    Vector3 asVector() const;

    bool isEqual(const Point3& b);

    void printf() const;// TODO Print
};


inline Point3 lerp(const Point3& a,const Point3& b, Scalar t){
    return a + t * (b - a);
}

inline Scalar squaredDist(const Point3 &a,const Point3 &b){
    return squaredNorm(a - b);
}

inline Scalar dist(const Point3 &a,const Point3 &b){
    return norm(a - b);
}
