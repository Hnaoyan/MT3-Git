﻿#pragma once
#include "DrawSet.h"

class Collision
{
public:
	/// <summary>
	/// 球と球の衝突判定
	/// </summary>
	/// <param name="sp1"></param>
	/// <param name="sp2"></param>
	/// <returns></returns>
	static bool IsCollision(const Sphere& sp1, const Sphere& sp2);
	/// <summary>
	/// 球と平面の衝突判定
	/// </summary>
	/// <param name="sp1"></param>
	/// <param name="plane"></param>
	/// <returns></returns>
	static bool IsCollision(const Sphere& sp1, const Plane& plane);
	/// <summary>
	/// 線と平面の衝突判定
	/// </summary>
	/// <param name="segment"></param>
	/// <param name="plane"></param>
	/// <returns></returns>
	static bool IsCollision(const Segment& segment, const Plane& plane);

};
