#pragma once

struct Vector3 {
	float x, y, z;
};

class Calc
{
public:
	Calc() {};
	~Calc() {};

	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

public:
	Vector3 Add(const Vector3& v1, const Vector3& v2);
	Vector3 Subtract(const Vector3& v1, const Vector3& v2);
	Vector3 Multiply(float scaler, const Vector3& v);
	Vector3 Normalize(const Vector3& v);

	float Dot(const Vector3& v1, const Vector3& v2);
	float Length(const Vector3& v);
public:

	static const int kColumnWidth = 60;

};
