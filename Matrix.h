#pragma once
struct Matrix4x4 {
	float m[4][4];
};
class Matrix
{
public:
	Matrix() {};
	~Matrix() {};

public:
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 Inverse(const Matrix4x4& m);
	Matrix4x4 Transpose(const Matrix4x4& m);
	Matrix4x4 MakeIdentity4x4();
private:
	static const int IndexX = 4;
	static const int IndexY = 4;
};

