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

	Matrix* matrix = nullptr;
	Render* render = nullptr;

	Segment segment;
	segment.diff = { 1.0f,0.5f,0.0f };
	segment.origin = { -0.6f,0.5f,0.0f };

	Triangle triangle;
	triangle.vertices[0] = { -1.0f,0.0f,0.0f };
	triangle.vertices[1] = { 0.0f,1.0f,0.0f };
	triangle.vertices[2] = { 1.0f,0.0f,0.0f };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	unsigned int color = BLACK;

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

		ImGui::Begin("Debug");
		ImGui::DragFloat3("camera.center", &cameraTranslate.x, 0.01f, -7.0f, 7.0f);
		ImGui::DragFloat3("camera.rotate", &cameraRotate.x, 0.01f, -3.0f, 3.0f);
		ImGui::DragFloat3("segment.Origin", &segment.origin.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat3("segment.Diff", &segment.diff.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat3("triangle.vert1", &triangle.vertices[0].x, 0.01f, -2.0f, 2.0f);
		ImGui::DragFloat3("triangle.vert2", &triangle.vertices[1].x, 0.01f, -2.0f, 2.0f);
		ImGui::DragFloat3("triangle.vert3", &triangle.vertices[2].x, 0.01f, -2.0f, 2.0f);

		ImGui::End();

		if (Collision::IsCollision(triangle,segment)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		Vector3 start = Matrix::Transform(Matrix::Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		Vector3 end = Matrix::Transform(Matrix::Transform(Vector::Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSet::DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawSet::DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, color);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);

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
