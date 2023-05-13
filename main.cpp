#include <Novice.h>
#include"Matrix.h"
#include "Render.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ImGuiManager.h"

const char kWindowTitle[] = "学籍番号";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

struct Sphere {
	Vector3 center;	// 中心点
	float radius;	// 半径
};

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
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
		if((int(zIndex) - 5) == 0){
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), BLACK);

		}
		else {
			Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y),
				int(screenVertex[1].x), int(screenVertex[1].y), 0xAAAAAAFF);
		}

	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20;	// 分割数
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision;	// 経度分割角度 φ
	const float kLatEvery = float(M_PI) / kSubdivision;	// 緯度分割角度 θ

	// 緯度の方向に分割 -π/2 ~ -π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat =  float((-1 * M_PI) / 2.0f) + kLatEvery * latIndex;	// 緯度 θ
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
				sphere.center.x + sphere.radius * std::cosf(lat + (float(M_PI) / kSubdivision)) * std::cosf(lon),
				sphere.center.y + sphere.radius * std::sinf(lat + (float(M_PI) / kSubdivision)),
				b.z = sphere.center.z + sphere.radius * std::cosf(lat + (float(M_PI) / kSubdivision)) * std::sinf(lon)
			};

			c = {
					sphere.center.x + sphere.radius * std::cosf(lat) * std::cosf(lon + (float(M_PI) * 2.0f / kSubdivision)),
					sphere.center.y + sphere.radius * std::sinf(lat),
					sphere.center.z + sphere.radius * std::cosf(lat) * std::sinf(lon + (float(M_PI) * 2.0f / kSubdivision))
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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix* matrix = nullptr;
	Render* render = nullptr;

	Sphere sphere;
	sphere.center = { 0,-25.0f,80.0f };
	sphere.radius = 10.0f;

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMatrix = Matrix::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = render->MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, Matrix::Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = render->MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		float posFloat[3] = { cameraTranslate.x,cameraTranslate.y,cameraTranslate.z };
		float rotateFloat[3] = { cameraRotate.x,cameraRotate.y,cameraRotate.z };

		float spPos[3] = { sphere.center.x,sphere.center.y,sphere.center.z };

		ImGui::Begin("Debug");
		ImGui::SliderFloat3("cameraPos", posFloat, -7.0f, 7.0f);
		ImGui::SliderFloat3("rotate", rotateFloat, -1.0f, 1.0f);
		ImGui::SliderFloat3("Sphre", spPos, -100.0f, 100.0f);
		ImGui::End();

		cameraTranslate = { posFloat[0],posFloat[1],posFloat[2] };
		cameraRotate = { rotateFloat[0],rotateFloat[1],rotateFloat[2] };
		sphere.center = { spPos[0],spPos[1],spPos[2] };

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
