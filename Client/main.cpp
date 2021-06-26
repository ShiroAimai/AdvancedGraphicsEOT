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
    t1.rotation = Rotation::rotationX(90);
    t1.scale = 4;
    t2.translation = Vector3(4,-3,1);
    t2.scale = 0.4;
    t2.rotation = Rotation::rotationZ(90);

    Point3 p(3,1,3);
    Point3 q0_a = t1.apply(p);
    Point3 q0_b = t2.apply (q0_a);
    Transform CumulatedTransform = t2 * t1;
    Point3 q1 = CumulatedTransform.apply ( p );

    check( q0_b.isEqual(q1) , "CUMULATE" );
}

void unitTestToFrom() {
	Vector3 from = Versor3::right().asVector();
	Vector3 to = Versor3::up().asVector();

    Matrix3 MatRot = Matrix3::toFrom(to, from);
    Vector3 Mat = MatRot.apply(from);
    Quaternion QuatRot = Quaternion::toFrom(to, from);
    Vector3 Quat = QuatRot.apply(from);
    AxisAngle AxisAngleRot = AxisAngle::toFrom(to, from);
    Vector3 axisAngle = AxisAngleRot.apply(from);

	check(axisAngle.IsEqual(Mat), "FROM AxisAngle TO Mat");
	check(axisAngle.IsEqual(Quat), "FROM AxisAngle TO Quat");
	check(Mat.IsEqual(Quat), "FROM Mat TO Quat");

    check(Mat .IsEqual(to), "Mat is equals to TO");
    check(Quat.IsEqual(to), "Quat is equals to TO");
    check(axisAngle.IsEqual(to), "AxisAngle is equals to TO");

	/*cout << "Mat"; Mat.printf(); cout << endl;
	cout << "Eul"; Eul.printf(); cout << endl;
	cout << "Quat"; Quat.printf(); cout << endl;
	cout << "AxisAngle"; axisAngle.printf(); cout << endl;*/
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

	check(mNotRot.isRot() == false, "Matrix3 is not a Rot");
	check(mRot.isRot() == true, "Matrix3 is Rot");
	
	Euler eRot(0, 30, 0);
	Euler eStillRot = Euler::from(mNotRot);

	check(eStillRot.isRot() == true, "Euler is still a Rot");
	check(eRot.isRot() == true, "Euler is Rot");
}

void unitTestConversionBetweenRepresentations()
{
    
    Matrix3 m = Matrix3::rotationY(30);
    Matrix3 resMat = Matrix3::from(AxisAngle::from(m));

	check(resMat.x.asVector().IsEqual(m.x.asVector()), "Matrix3 Conversion X");
	check(resMat.y.asVector().IsEqual(m.y.asVector()), "Matrix3 Conversion Y");
	check(resMat.z.asVector().IsEqual(m.z.asVector()), "Matrix3 Conversion Z");

	AxisAngle axisAngle = AxisAngle::rotationY(30);
    AxisAngle resAxisAngle = AxisAngle::from(Quaternion::from(m));

	check(resAxisAngle.axis.asVector().IsEqual(axisAngle.axis.asVector()), "AxisAngle Conversion Axis");
	check(abs(resAxisAngle.angle - axisAngle.angle) < EPSILON, "AxisAngle Conversion Angle");

    Quaternion quat = Quaternion::rotationY(30);
    Quaternion resQuat = Quaternion::from(AxisAngle::from(m));

	check(resQuat.v.IsEqual(quat.v), "Quaternion Conversion Immaginary Part");
	check(abs(resQuat.w - quat.w) < EPSILON, "Quaternion Conversion Real Part");
}

int main()
{
    unitTestInverse();
    cout << endl;
    unitTestCumulate();
    cout << endl;
    unitTestIsRot();
    cout << endl;
    unitTestConversionBetweenRepresentations();
    cout << endl;
    unitTestToFrom();
    cout << endl;

    return 0;
}
