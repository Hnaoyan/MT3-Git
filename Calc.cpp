#include "Calc.h"
#include<math.h>
#include<Novice.h>

void Calc::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + this->kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + this->kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + this->kColumnWidth * 3, y, "%s", label);
}

Vector3 Calc::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 Calc::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

Vector3 Calc::Multiply(float scaler, const Vector3& v) {
	Vector3 result;

	result.x = scaler * v.x;
	result.y = scaler * v.y;
	result.z = scaler * v.z;

	return result;
}

Vector3 Calc::Normalize(const Vector3& v) {
	Vector3 result = v;
	float length = Length(v);
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

float Calc::Dot(const Vector3& v1, const Vector3& v2) {
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}

float Calc::Length(const Vector3& v) {
	float length = float(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return length;
}