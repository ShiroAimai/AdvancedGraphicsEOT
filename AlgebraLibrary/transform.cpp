#include "pch.h"
#include "transform.h"

// constructor: is the ide
Transform::Transform() :scale(1), rotation(), translation(0, 0, 0) {}

// description of the local frame!
Point3 Transform::origin() const { return translation.asPoint(); }
Versor3 Transform::left() const { return -rotation.axisX(); }
Versor3 Transform::right()const { return +rotation.axisX(); }
Versor3 Transform::up() const { return -rotation.axisY(); }
Versor3 Transform::down()const { return +rotation.axisY(); }
Versor3 Transform::forward() const { return -rotation.axisZ(); }
Versor3 Transform::backward()const { return +rotation.axisZ(); }

Versor3 Transform::apply(Versor3 dir) {
    // apply only r
    return rotation.apply(dir);
}

Vector3 Transform::apply(Vector3 v) {
    // apply s r
    return rotation.apply(v * scale);
}

Point3 Transform::apply(Point3 p) { // apply s r t
    // apply s r t
    return rotation.apply(p.scaled(scale)) + translation;
}

// inverse out-of-place
Transform Transform::inverse() const {
    Transform result;
    result.scale = 1 / scale;
    result.rotation = rotation.inverse();
    result.translation = result.rotation.apply((-translation) * result.scale);
    return result;
}


void Transform::invert() // TODO T-invert  (in-place)
{

}

// CUMULATE: first b, then *this
Transform Transform::operator * (const Transform& b) {
    Transform result;
    result.scale = scale * b.scale;
    result.rotation = rotation * b.rotation;
    result.translation = b.translation * scale + translation;
    return result;
}

// fills a column-major Scalar 4x4 zmatrix for DirectX (or OpenGL)
// vector d is already allocated
void Transform::fillDirectXMatrix(Scalar d[]) {
    // TODO
}

// places this transform in the given origin, looking (Z-axis) toward target, given the up vector
void Transform::place(Point3 origin, Point3 target, Versor3 up) {
    // TODO: use methods
}

void Transform::printf() const {} // TODO
