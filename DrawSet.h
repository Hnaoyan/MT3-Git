#pragma once
#include"Matrix.h"
#include "Render.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct Sphere {
	Vector3 center;	// 中心点
	float radius;	// 半径
};

struct Line {
	Vector3 origin;	// 始点
	Vector3 diff;	// 終点への差分ベクトル
};

struct Ray {
	Vector3 origin;	// 始点
	Vector3 diff;	// 終点への差分ベクトル
};

struct Segment {
	Vector3 origin;	// 始点
	Vector3 diff;	// 終点への差分ベクトル
};

class DrawSet
{
public:
	static void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
	static void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	static Vector3 Project(const Vector3& v1, const Vector3& v2);
	static Vector3 ClosetPoint(const Vector3& point, const Segment& segment);

};
