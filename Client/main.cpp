#include <iostream>
#include <math.h>

#include "transform.h"

using std::cout;
using std::endl;

void check(bool condition, std::string descr ){
    std::cout << "Test " << descr << ": "
              << ((condition)?"PASSED":"FAILED" )
              << "\n";
}

void unitTestInverse(){
    Transform t;
    t.translation = Vector3(2,0,0);
    t.scale = 3;

    Point3 p0,q,p1;

    q = t.apply(p0);

    Transform ti = t.inverse();
    p1 = ti.apply(q); // VOGLIO RIOTTENERE p

    check( p0.isEqual(p1) , "INVERSE");
}

void unitTestCumulate(){
    Transform t1,t2;
    t1.translation = Vector3(2,0,0);
    t1.scale = 4;
    t2.translation = Vector3(4,-3,1);
    t2.scale = 0.4;

    Point3 p(3,1,3);
    Point3 q0 = t2.apply ( t1.apply(p) );
    Point3 q1 = (t2*t1).apply ( p );

    check( q0.isEqual(q1) , "CUMULATE" );

}

void unitTestToFrom() {
	Vector3 from = Vector3(Versor3::right().asVector());
	Vector3 to = Vector3(Versor3::forward().asVector());

    Vector3 Mat = Matrix3::toFrom(to, from).apply(from);
	Vector3 Eul = Euler::toFrom(to, from).apply(from);
	Vector3 Quat = Quaternion::toFrom(to, from).apply(from);
	Vector3 AxisAngle = AxisAngle::toFrom(to, from).apply(from);

	check(Eul.IsEqual(AxisAngle), "FROM Eul TO AxisAngle");
	check(AxisAngle.IsEqual(Mat), "FROM AxisAngle TO Mat");
	check(AxisAngle.IsEqual(Quat), "FROM AxisAngle TO Quat");
	check(Mat.IsEqual(Quat), "FROM Mat TO Quat");
	check(Eul.IsEqual(Quat), "FROM Eul TO Quat");
	check(Eul.IsEqual(Mat), "FROM Eul TO Mat");

}

void unitTestIsRot() {
    Quaternion qPoint(Point3::origin().asVector(), 0);
    Quaternion qRot;

    check(qPoint.isRot() == false, "Quaternion is not Rot");
    check(qRot.isRot() == true, "Quaternion is Rot");

    AxisAngle aPoint;
    AxisAngle aRot(Versor3::forward(), DegToRad(30));

	check(aPoint.isRot() == false, "AxisAngle is not Rot");
	check(aRot.isRot() == true, "AxisAngle is Rot");
    
    Matrix3 mNotRot(
        1, 1, 1,
        0, 0, 0,
        0, 0, 0
    );
    Matrix3 mRot;

	check(mNotRot.isRot() == false, "Matrix3 is not Rot");
	check(mRot.isRot() == true, "Matrix3 is Rot");
	
    Euler eNotRot = Euler::from(mNotRot);
	Euler eRot(0, 30, 0);

	check(eNotRot.isRot() == false, "Euler is not Rot");
	check(eRot.isRot() == true, "Euler is Rot");
}

void unitTestConversionBetweenRepresentations()
{
    Euler e(10, 0, 0);    
    Euler resEuler = Euler::from(Matrix3::from(e));

    check(abs(e.Pitch - resEuler.Pitch) < EPSILON, "Euler Conversion X");
    check(abs(e.Yaw - resEuler.Yaw) < EPSILON, "Euler Conversion Y");
    check(abs(e.Roll - resEuler.Roll) < EPSILON, "Euler Conversion Z");
    
    Matrix3 m = Matrix3::rotationY(30);
    Matrix3 resMat = Matrix3::from(Euler::from(m));

	check(resMat.x.asVector().IsEqual(m.x.asVector()), "Matrix3 Conversion X");
	check(resMat.y.asVector().IsEqual(m.y.asVector()), "Matrix3 Conversion Y");
	check(resMat.z.asVector().IsEqual(m.z.asVector()), "Matrix3 Conversion Z");
}

int main()
{
    unitTestInverse();
    unitTestCumulate();
    unitTestIsRot();
    unitTestConversionBetweenRepresentations();
    unitTestToFrom();
    return 0;
}
