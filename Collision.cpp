﻿#include "Collision.h"
#include "MathCalc.h"
#include "Vector.h"
#include<algorithm>

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

bool Collision::IsCollision(const Triangle& triangle, const Segment& segment) {

	Vector3 v01 = Vector::Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v12 = Vector::Subtract(triangle.vertices[2], triangle.vertices[1]);
	Vector3 v20 = Vector::Subtract(triangle.vertices[0], triangle.vertices[2]);

	Vector3 crossNormal = MathCalc::Cross(v01, v12);
	Vector3 Normal = MathCalc::Normalize(crossNormal);
	float crossDis = MathCalc::Dot(Normal, triangle.vertices[0]);

	float dot = MathCalc::Dot(Normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (crossDis - MathCalc::Dot(segment.origin, Normal)) / dot;
	if (0.0f < t && t < 1.0f) {

		Vector3 point = Vector::Add(segment.origin, Vector::Multiply(t, segment.diff));

		Vector3 v1p = Vector::Subtract(point, triangle.vertices[1]);
		Vector3 v2p = Vector::Subtract(point, triangle.vertices[2]);
		Vector3 v0p = Vector::Subtract(point, triangle.vertices[0]);

		Vector3 cross01 = MathCalc::Cross(v01, v1p);
		Vector3 cross12 = MathCalc::Cross(v12, v2p);
		Vector3 cross20 = MathCalc::Cross(v20, v0p);

		if (MathCalc::Dot(cross01, Normal) >= 0.0f &&
			MathCalc::Dot(cross12, Normal) >= 0.0f &&
			MathCalc::Dot(cross20, Normal) >= 0.0f) {
			return true;
		}
	}
	return false;
}

bool Collision::IsAABBCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&	// X軸
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&	// Y軸
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {	// Z軸
		return true;
	}
	return false;
}

bool Collision::IsCollision(const AABB& aabb, const Sphere& sphere) {
	// 最近接点を求める
	Vector3 closestPoint{std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z)};

	// 最近接点と球の中心との距離を求める
	float distance = MathCalc::Length(Vector::Subtract(closestPoint, sphere.center));
	// 距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		return true;
	}

	return false;
}