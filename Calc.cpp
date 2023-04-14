#include "Calc.h"
#include<assert.h>

Matrix4x4 Calc::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}


Matrix4x4 Calc::MakeScaleMatrix(const Vector3& translate) {
	Matrix4x4 result;

	result.m[0][0] = translate.x;
	result.m[1][1] = translate.y;
	result.m[2][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}

Vector3 Calc::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] * 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] * 1.0f * matrix.m[3][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] * 1.0f * matrix.m[3][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}