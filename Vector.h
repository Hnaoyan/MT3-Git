#pragma once
#include "Vector3.h"

class Vector {
public:
	// 加算
	static Vector3 Add(const Vector3& v1, const Vector3& v2);
	// 減算
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	// 乗算
	static Vector3 Multiply(float scaler, const Vector3& v);

};

