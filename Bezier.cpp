#include "Bezier.h"

Vector3 Bezier::Lerp(const Vector3& a, const Vector3& b, float t)
{
	Vector3 returnTmp;
	returnTmp.x = (t)*a.x + (1.0f - t) * b.x;
	returnTmp.y = (t)*a.y + (1.0f - t) * b.y;
	returnTmp.z = (t)*a.z + (1.0f - t) * b.z;
    return returnTmp;
}

Vector3 Bezier::BezierPoint(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 p0p1 = Lerp(p0, p1, t);
	Vector3 p1p2 = Lerp(p1, p2, t);
	Vector3 p = Lerp(p0p1, p1p2, t);

	return p;
}
