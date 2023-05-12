#include <Novice.h>
#include"Matrix.h"
#include "Render.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "学籍番号";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;
const int kColumnWidth = 60;
const int kRowHeight = 20;

struct Sphere {
	Vector3 center;	// 中心点
	float radius;	// 半径
};

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);
	Vector3 worldVertex[2];
	Vector3 screenVertex[2];
	Vector3 ndcVertex;
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		worldVertex[0] = {xIndex* ,0,kGridEvery };
		worldVertex[1] = {};
		// スクリーン座標系まで変換をかける
		 
		
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)
	}
	//// 左から右も同じように順々に引いていく
	//for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
	//	// 奥から手前が左右に変わるだけ

	//}
}

//void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
//	const uint32_t kSubdivision = 0;
//	const float kLonEvery = 0;
//	const float kLatEvery = 0;
//
//	// 緯度の方向に分割 -π/2 ~ -π/2
//	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
//		float lat =  (-M_PI) / 2.0f + kLatEvery * latIndex;	// 緯度
//		// 緯度の方向に分割
//		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
//			float lon = lonIndex * kLonEvery; // 現在の経度
//			// World座標系でのa,b,cを求める
//			Vector3 a, b, c;
//
//		}
//
//	}
//}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				int(x + column * kColumnWidth), int(y + (row + 1) * kRowHeight), "%6.02f", matrix.m[row][column]
			);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
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
	sphere.center = { 0,0,0 };
	sphere.radius = 10.0f;

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Matrix4x4 viewportMatrix = Render::MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);
	Matrix4x4 projectionMatrix = Render::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

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



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//DrawGrid(projectionMatrix, viewportMatrix);

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
