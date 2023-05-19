#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Render
{
public:

	// 1.PerspectiveFov
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	// 2.Orthographic
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	// 3.Viewport
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
};

