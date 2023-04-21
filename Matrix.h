#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

class Matrix
{
public:
	Matrix() {};
	~Matrix() {};

public:
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 Inverse(const Matrix4x4& m);
	Matrix4x4 Transpose(const Matrix4x4& m);
	Matrix4x4 MakeIdentity4x4();
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	Vector3 Multiply(float scaler, const Vector3& v);
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);


private:
	static const int IndexX = 4;
	static const int IndexY = 4;
};

