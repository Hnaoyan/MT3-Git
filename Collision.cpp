#include "Collision.h"
#include "MathCalc.h"
#include "Vector.h"

bool Collision::IsCollision(const Sphere& sp1, const Sphere& sp2) {
	Sphere sphereDistance = sp1;
	// 2球体の距離を求める
	sphereDistance.center = sphereDistance.center - sp2.center;
	float distance = MathCalc::Length(sphereDistance.center);
	// 半径の合計よりも短いか
	if (distance <= sp1.radius + sp2.radius) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const Sphere& sp1, const Plane& plane) {
	Sphere sphereDistance = sp1;
	// 2球体の距離を求める
	Vector3 planePoint = MathCalc::Normalize(plane.normal);
	planePoint = { planePoint.x * plane.distance,planePoint.y * plane.distance, planePoint.z * plane.distance };
	float distance = fabsf(MathCalc::Dot(plane.normal, Vector::Subtract(sp1.center,planePoint)));

	// 半径の合計よりも短いか
	if (distance <= sp1.radius) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const Segment& segment, const Plane& plane) {
	// 法線と線の内積
	float dot = MathCalc::Dot(plane.normal, segment.diff);

	// 
	if (dot == 0.0f) {
		return false;
	}
	// tを求める
	float t = (plane.distance - MathCalc::Dot(segment.origin, plane.normal)) / dot;

	if (t > 0 && t < 1) { 
		return true;
	}
	return false;
}