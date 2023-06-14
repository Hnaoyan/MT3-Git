#pragma once
#include "DrawSet.h"

class Collision
{
public:
	static bool IsCollision(const Sphere& sp1, const Sphere& sp2);
	static bool IsCollision(const Sphere& sp1, const Plane& plane);


};

