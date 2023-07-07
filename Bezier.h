#pragma once
#include "Vector3.h"

class Bezier
{
public:
	/// <summary>
	/// Lerp関数
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	/// <summary>
	/// Bezierの点を取得する関数
	/// </summary>
	/// <param name="p0"></param>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	static Vector3 BezierPoint(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);


};

