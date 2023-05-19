#include "Vector.h"

Vector3 Vector::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 Vector::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

Vector3 Vector::Multiply(float scaler, const Vector3& v) {
	Vector3 result;

	result.x = scaler * v.x;
	result.y = scaler * v.y;
	result.z = scaler * v.z;

	return result;
}
