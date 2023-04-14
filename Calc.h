#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>

class Calc
{
public:
	Calc() {};
	~Calc() {};

public:
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

};

