#pragma once
#include<Matrix4x4.h>
#include<Vector3.h>

class Matrix
{
public:
	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	Matrix4x4 Multiply(Matrix4x4& m1, Matrix4x4& m2);
	Vector3 Multiply(float scaler, const Vector3& v);
};

