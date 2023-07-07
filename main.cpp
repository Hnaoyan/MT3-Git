#include <Novice.h>
#include "DrawSet.h"
#include "Matrix.h"
#include "Render.h"
#include "ImGuiManager.h"
#include "MathCalc.h"
#include "Collision.h"
#include "Vector.h"

const char kWindowTitle[] = "学籍番号";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	unsigned int color = BLACK;

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	Sphere sphere[3];
	for (int i = 0; i < 3; i++) {
		sphere[i].center = translates[i];
		sphere[i].radius = 0.05f;
	}

	Matrix4x4 worldMat[3];

	Matrix4x4 VPJMatrix[3];

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
		
		worldMat[0] = Matrix::MakeAffineMatrix(scales[0], rotates[0], sphere[0].center);
		worldMat[1] = Matrix::Multiply(Matrix::MakeAffineMatrix(scales[1], rotates[1], sphere[1].center), worldMat[0]);
		worldMat[2] = Matrix::Multiply(Matrix::MakeAffineMatrix(scales[2], rotates[2], sphere[2].center), worldMat[1]);

		Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Render::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, Matrix::Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = Render::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		VPJMatrix[0] = Matrix::Multiply(worldMat[0], Matrix::Multiply(viewMatrix, projectionMatrix));
		VPJMatrix[1] = Matrix::Multiply(worldMat[1], Matrix::Multiply(viewMatrix, projectionMatrix));
		VPJMatrix[2] = Matrix::Multiply(worldMat[2], Matrix::Multiply(viewMatrix, projectionMatrix));

		ImGui::Begin("Debug");
		ImGui::DragFloat3("camera.center", &cameraTranslate.x, 0.01f, -7.0f, 7.0f);
		ImGui::DragFloat3("camera.rotate", &cameraRotate.x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("trans[0]", &translates[0].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("rotate[0]", &rotates[0].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("scale[0]", &scales[0].x, 0.01f, -3.0f, 3.0f);

		ImGui::DragFloat3("trans[1]", &translates[1].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("rotate[1]", &rotates[1].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("scale[1]", &scales[1].x, 0.01f, -3.0f, 3.0f);

		ImGui::DragFloat3("trans[2]", &translates[2].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("rotate[2]", &rotates[2].x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("scale[2]", &scales[2].x, 0.01f, -3.0f, 3.0f);

		ImGui::End();

		for (int i = 0; i < 3; i++) {
			sphere[i].center = translates[i];
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSet::DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawSet::DrawSphere(sphere[0], worldMatrix, viewportMatrix, RED);
		DrawSet::DrawSphere(sphere[1], VPJMatrix[1], viewportMatrix, GREEN);
		DrawSet::DrawSphere(sphere[2], VPJMatrix[2], viewportMatrix, BLUE);

		Novice::DrawLine(int(translates[0].x), int(translates[0].y), int(translates[1].x), int(translates[1].y), WHITE);
		//Novice::DrawLine(int(sphere[1].center.x), int(sphere[1].center.y), int(sphere[2].center.x), int(sphere[2].center.y), WHITE);


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
