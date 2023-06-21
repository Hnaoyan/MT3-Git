#include "DrawSet.h"
#include <Novice.h>
#include <cmath>
#include "MathCalc.h"
#include "Vector.h"

void DrawSet::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;	// Gridの半分の幅
	const uint32_t kSubdivision = 10;	// 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);	// 1つ分の長さ

	Vector3 worldVertex[2] = {};
	Vector3 screenVertex[2] = {};
	Vector3 ndcVertex[2] = {};
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		worldVertex[0] = { -kGridHalfWidth ,0,kGridEvery * (int(xIndex) - 5) };
		worldVertex[1] = { kGridHalfWidth,0,kGridEvery * (int(xIndex) - 5) };
		// スクリーン座標系まで変換をかける
		ndcVertex[0] = Matrix::Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = Matrix::Transform(ndcVertex[0], viewportMatrix);

		ndcVertex[1] = Matrix::Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = Matrix::Transform(ndcVertex[1], viewportMatrix);
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)
		if ((int(xIndex) - 5) == 0) {
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), BLACK);

		}
		else {
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), 0xAAAAAAFF);
		}
	}

	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		// 奥から手前が左右に変わるだけ
				// 上の情報を使ってワールド座標系上の始点と終点を求める
		worldVertex[0] = { kGridEvery * (int(zIndex) - 5) ,0,-kGridHalfWidth };
		worldVertex[1] = { kGridEvery * (int(zIndex) - 5),0,kGridHalfWidth };
		// スクリーン座標系まで変換をかける
		ndcVertex[0] = Matrix::Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = Matrix::Transform(ndcVertex[0], viewportMatrix);

		ndcVertex[1] = Matrix::Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = Matrix::Transform(ndcVertex[1], viewportMatrix);
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)
		if ((int(zIndex) - 5) == 0) {
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), BLACK);

		}
		else {
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), 0xAAAAAAFF);
		}

	}
}

void DrawSet::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;	// 分割数
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision;	// 経度分割角度 φ
	const float kLatEvery = float(M_PI) / kSubdivision;	// 緯度分割角度 θ

	// 緯度の方向に分割 -π/2 ~ -π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float((-1 * M_PI) / 2.0f) + kLatEvery * latIndex;	// 緯度 θ
		// 経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度 φ
			// World座標系でのa,b,cを求める
			Vector3 a, b, c;
			Vector3 ndcA, ndcB, ndcC;
			Vector3 scrA, scrB, scrC;

			a = {
				sphere.center.x + sphere.radius * std::cosf(lat) * std::cosf(lon),
				sphere.center.y + sphere.radius * std::sinf(lat),
				sphere.center.z + sphere.radius * std::cosf(lat) * std::sinf(lon)
			};

			b = {
				sphere.center.x + sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon),
				sphere.center.y + sphere.radius * std::sinf(lat + kLatEvery),
				b.z = sphere.center.z + sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon)
			};

			c = {
					sphere.center.x + sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery),
					sphere.center.y + sphere.radius * std::sinf(lat),
					sphere.center.z + sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery)
			};

			ndcA = Matrix::Transform(a, viewProjectionMatrix);
			scrA = Matrix::Transform(ndcA, viewportMatrix);
			ndcB = Matrix::Transform(b, viewProjectionMatrix);
			scrB = Matrix::Transform(ndcB, viewportMatrix);
			ndcC = Matrix::Transform(c, viewProjectionMatrix);
			scrC = Matrix::Transform(ndcC, viewportMatrix);

			Novice::DrawLine(int(scrA.x), int(scrA.y), int(scrB.x), int(scrB.y), color);
			Novice::DrawLine(int(scrA.x), int(scrA.y), int(scrC.x), int(scrC.y), color);
		}

	}
}

void DrawSet::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Vector::Multiply(plane.distance, plane.normal);	// 1
	Vector3 perpendiculars[4];
	perpendiculars[0] = MathCalc::Normalize(Perpendicular(plane.normal));	// 2
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z }; // 3
	perpendiculars[2] = MathCalc::Cross(plane.normal, perpendiculars[0]);	// 4
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };	// 5
	// 6
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Vector::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Vector::Add(center, extend);
		points[index] = Matrix::ScreenChange(point, viewProjectionMatrix, viewportMatrix);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);

}

void DrawSet::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 screenVerities[3];
	for (int i = 0; i < 3; i++) {
		screenVerities[i] = Matrix::Transform(Matrix::Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle(int(screenVerities[0].x), int(screenVerities[0].y), int(screenVerities[1].x), int(screenVerities[1].y),
		int(screenVerities[2].x), int(screenVerities[2].y), color, kFillModeWireFrame);
}

Vector3 DrawSet::Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = MathCalc::Dot(v1,MathCalc::Normalize(v2)) * MathCalc::Normalize(v2).x;
	result.y = MathCalc::Dot(v1, MathCalc::Normalize(v2)) * MathCalc::Normalize(v2).y;
	result.z = MathCalc::Dot(v1, MathCalc::Normalize(v2)) * MathCalc::Normalize(v2).z;

	return result;
}

Vector3 DrawSet::ClosetPoint(const Vector3& point, const Segment& segment) {
	Vector3 result;
	Vector3 projectPoint;
	projectPoint = Vector::Subtract(point, segment.origin);
	Vector3 project = Project(projectPoint, segment.diff);

	result = Vector::Add(segment.origin, project);

	return result;
}

Vector3 DrawSet::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };

}