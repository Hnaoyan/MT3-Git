#include "Matrix.h"
#include<assert.h>
#include <cmath>

Matrix4x4 Matrix::Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][x] + m2.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix::Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][x] - m2.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[y][x] += m1.m[y][k] * m2.m[k][x];
			}
		}
	}
	return result;
}

Matrix4x4 Matrix::Transpose(const Matrix4x4& m) {
	Matrix4x4 result;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m.m[x][y];
		}
	}
	return result;
}

Matrix4x4 Matrix::Inverse(const Matrix4x4& m) {
	Matrix4x4 result = {};
	float det = 0;
	det += (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]);
	det += (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]);
	det += (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]);

	det -= (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]);
	det -= (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]);
	det -= (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]);

	det -= (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]);
	det -= (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]);
	det -= (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]);

	det += (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]);
	det += (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]);
	det += (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]);

	det += (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]);
	det += (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]);
	det += (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]);

	det -= (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]);
	det -= (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]);
	det -= (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]);

	det -= (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]);
	det -= (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]);
	det -= (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]);

	det += (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]);
	det += (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]);
	det += (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	if (det != 0) {
		{result.m[0][0] = (1.0f / det) *
			(m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
				- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][1] = (1.0f / det) *
			(-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
				+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][2] = (1.0f / det) *
			(+m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
				- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
		result.m[0][3] = (1.0f / det) *
			(-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
				+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]); }

		{result.m[1][0] = (1.0f / det) *
			(-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
				+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][1] = (1.0f / det) *
			(m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
				- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][2] = (1.0f / det) *
			(-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
				+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
		result.m[1][3] = (1.0f / det) *
			(m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
				- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]); }

		{result.m[2][0] = (1.0f / det) *
			(m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
				- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][1] = (1.0f / det) *
			(-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
				+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][2] = (1.0f / det) *
			(m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
				- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
		result.m[2][3] = (1.0f / det) *
			(-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
				+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]); }

		result.m[3][0] = (1.0f / det) *
			(-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
				+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
		result.m[3][1] = (1.0f / det) *
			(m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
				- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);


		result.m[3][2] = (1.0f / det) *
			(-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
				+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
		result.m[3][3] = (1.0f / det) *
			(m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
				- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);
	}
	return result;
}

Matrix4x4 Matrix::MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (x == y) {
				result.m[y][x] = 1;
			}
		}
	}
	return result;
}

Matrix4x4 Matrix::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = {};
	Matrix4x4 matrixX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 matrixY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 matrixZ = MakeRotateZMatrix(rotate.z);
	Matrix4x4 matrixRotate = Multiply(matrixX, Multiply(matrixY, matrixZ));

	result.m[0][0] = scale.x * matrixRotate.m[0][0];
	result.m[0][1] = scale.x * matrixRotate.m[0][1];
	result.m[0][2] = scale.x * matrixRotate.m[0][2];
	result.m[1][0] = scale.y * matrixRotate.m[1][0];
	result.m[1][1] = scale.y * matrixRotate.m[1][1];
	result.m[1][2] = scale.y * matrixRotate.m[1][2];
	result.m[2][0] = scale.z * matrixRotate.m[2][0];
	result.m[2][1] = scale.z * matrixRotate.m[2][1];
	result.m[2][2] = scale.z * matrixRotate.m[2][2];

	result.m[3][3] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

Matrix4x4 Matrix::MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[2][1] = std::sinf(-radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Matrix::MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = std::cosf(radian);
	result.m[0][2] = std::sinf(-radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Matrix::MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][0] = std::sinf(-radian);
	result.m[1][1] = std::cosf(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Matrix::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 Matrix::ScreenChange(const Vector3& center, const Matrix4x4& ViewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	Vector3 result;
	result = Transform(center, ViewProjectionMatrix);
	result = Transform(result, viewportMatrix);
	return result;
}
