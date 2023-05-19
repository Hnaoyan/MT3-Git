#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

class Matrix
{
public:
	Matrix() {};
	~Matrix() {};

public:
	///<summary>
	/// 行列
	///</summary>
	// 加算
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	// 減算
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	// 乗算
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	// 逆行列
	static Matrix4x4 Inverse(const Matrix4x4& m);
	static Matrix4x4 Transpose(const Matrix4x4& m);
	static Matrix4x4 MakeIdentity4x4();
	//　アフィン変換
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	// 回転
	static Matrix4x4 MakeRotateXMatrix(float radian);
	static Matrix4x4 MakeRotateYMatrix(float radian);
	static Matrix4x4 MakeRotateZMatrix(float radian);

	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	// スクリーン座標へ変換
	static Vector3 ScreenChange(const Vector3& center, const Matrix4x4& ViewProjectionMatrix, const Matrix4x4& viewportMatrix);

};

