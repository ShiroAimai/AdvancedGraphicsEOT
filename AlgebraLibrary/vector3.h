#pragma once

class Point3; // prometto che esiste una classe Point3 da qualche parte
class Versor3;

using Scalar = double;

class Vector3{
public:
    Scalar x,y,z;

    // constructors
    Vector3();
    Vector3(Scalar _x, Scalar _y, Scalar _z);

    static Vector3 right()   { return Vector3(+1, 0, 0);}
    static Vector3 left()    { return Vector3(-1, 0, 0);}
    static Vector3 up()      { return Vector3( 0,+1, 0);}
    static Vector3 down()    { return Vector3( 0,-1, 0);}
    static Vector3 forward() { return Vector3( 0, 0,+1);}
    static Vector3 backward(){ return Vector3( 0, 0,-1);}

    bool IsEqual(const Vector3& other) const;

    // access to the coordinates: to write them
    Scalar& operator[] (int i);

    // access to the coordinates: to read them
    Scalar operator[] (int i) const;

    // vector sum
    Vector3 operator+(const Vector3& b) const;

    // vector-sum: in-place version
    void operator+=(const Vector3& b);

    Vector3 operator-(const Vector3& b) const;

    // unitary minus operator
    Vector3 operator-() const;

    Vector3 operator*(const Vector3& b) const;

    void operator *= (const Vector3& b);

    Vector3 operator*(Scalar k) const;

    void operator *= (Scalar k);

    Vector3 operator/(Scalar k) const;

    void operator /= (Scalar k);

    void printf() const;// TODO Print

	Point3 asPoint() const;
	Versor3 asVersor() const;
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
    return dot(a,a) ;
}

inline Scalar norm(const Vector3 &a){
    return sqrt(squaredNorm(a));
}

inline Vector3 operator*( Scalar k, const Vector3& a)
{ 
    return a*k; 
}

inline Vector3 lerp( const Vector3& a,const Vector3& b, Scalar t){
    return (1-t)*a + t*b;
}


