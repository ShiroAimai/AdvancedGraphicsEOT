#pragma once


// problems.h:
// a small set of matematical problems

#include "pch.h"
#include "vector3.h"
#include "point3.h"
#include "versor3.h"
#include "quaternion.h"

// POD -- Plain Old Data
struct Ray{
    Point3 p;
    Vector3 v;
};

struct Sphere{
    Point3 c;
    Scalar r;
};

struct Plane{
    // TODO-plane: fill
    Point3 origin;
    Vector3 width, height;
};

const Point3 NO_INTERSECTION(666,666,666);

Point3 intersect(const Ray &r, const Sphere &s){
    Scalar a = dot( r.v , r.v );
    Scalar b = 2*dot( r.p-s.c , r.v );
    Scalar c = dot(r.p-s.c,r.p-s.c) - s.r * s.r;

    // euqation is: a*k^2 + b*k + c == 0

    Scalar delta = b*b-4*a*c;
    if (delta < 0) return NO_INTERSECTION;

    Scalar k = (-b -sqrt(delta)) / (2*a);
    if (k<0) return NO_INTERSECTION;
    return r.p + k * r.v;
}

Point3 intersect(const Ray& r, const Plane& p) {
    // TODO: P-inter-plane
    Vector3 planeNormal = cross(p.width, p.height);
    Scalar divider = dot(r.v, planeNormal);
    if (abs(divider) > EPSILON) //if ray is not ortho to plane then
    {
        Scalar RayDistance = (dot(-(r.p - p.origin), planeNormal)) / divider;
		return r.p + (r.v * RayDistance);
    }

    return NO_INTERSECTION;
}

// does a eye in a given position sees the target, given the angle cone and maxDist?
bool isSeen(const Versor3& ViewDir, Point3& eye, const Point3& target, Scalar angleDeg, Scalar maxDist) {
    // TODO: isSeen
    Vector3 DirToTarget = target - eye;
    if (squaredNorm(DirToTarget) > (maxDist * maxDist)) return false; //out of  range
    
    Scalar halfFOV = cos(angleDeg / 2.0);
    return dot(normalize(DirToTarget), ViewDir) > halfFOV;
}

// returns the reflected direction of something bouncing in n
Versor3 reflect( const Versor3 &d, const Versor3 &n){
    // TODO: P-reflect
    //Solution https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    // r = d - 2(dot(d,n)n
    return normalize(d.asVector() - (2 * dot(d, n) * n));
}

bool areCoplanar(const Versor3 &a, const Versor3 &b, const Versor3 &c){
    // TODO: P-coplanar
    /*Scalar cosAtoB = dot(a, b);
    Scalar cosAtoC = dot(a, c);
    //check they're all parallel by checking their cosine
    return cosAtoB <= EPSILON && cosAtoC <= EPSILON;*/

    return dot(a, cross(b, c)) <= EPSILON; //SCALAR TRIPLE PRODUCT https://www.youtube.com/watch?v=FENmqu40jUc
}

// normal of a plane, given three points
Versor3 planeNormal(const Point3 &a, const Point3 &b, const Point3 &c){
    // TODO: P-palneNorm
    
    Vector3 DirAToB = b - a;
    Vector3 DirAToC = c - a;

    return normalize(cross(DirAToB, DirAToC));
}

// return a versor as similar as possible to a, but ortogonal to b
Versor3 orthogonalize( const Versor3 &a, const Versor3 &b ){
    // TODO: P-ortogonalize
    return normalize(cross(b, normalize(cross(a, b))));
}

// a bullet is in position pa and has velocity va
// a target is in position pb and has velocity vb
// returns the position of the target in the moment it is closest to the bullet
Point3 hitPos( const Point3 &pa, const Vector3 &va, const Point3 &pb, const Vector3 &vb ){
    // TODO: P-hitPos
    return Point3();
}



