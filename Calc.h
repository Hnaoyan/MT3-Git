#pragma once
#include<Matrix4x4.h>
#include<Vector3.h>

class Calc
{
public:
	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	Vector3 Multiply(float scaler, const Vector3& v);
};

