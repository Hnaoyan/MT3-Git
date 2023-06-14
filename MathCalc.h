#pragma once
#include <Vector2.h>
#include <Vector3.h>
class MathCalc
{

public:	
	// 長さ
	static float Length(const Vector2& v1);
	static float Length(const Vector3& v1);
	// 内積
	static float Dot(const Vector2& v1, const Vector2& v2);
	static float Dot(const Vector3& v1, const Vector3& v2);
	// クロス積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	// 距離
	static float Distance(const Vector2& v1, const Vector2& v2);
	static float Distance(const Vector3& v1, const Vector3& v2);

	static Vector2 Normalize(const Vector2& v);
	static Vector3 Normalize(const Vector3& v);
	static float Clamp(const float& min, const float& max, const float& t);

};

