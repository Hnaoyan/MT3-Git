#include <Novice.h>
#include "DrawSet.h"
#include "Matrix.h"
#include "Render.h"
#include "ImGuiManager.h"
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

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = DrawSet::Project(Vector::Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = DrawSet::ClosetPoint(point, segment);


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

		ImGui::Begin("Debug");
		float float3[3] = { point.x,point.y,point.z };
		ImGui::SliderFloat3("point", float3, -7.0f, 7.0f);
		point = { float3[0],float3[1],float3[2] };
		ImGui::InputFloat3("SegmentOrigin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("SegmentDiff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		Sphere pointSphere{ point,0.01f };
		Sphere closestPointSphere{ closestPoint,0.01f };



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawSet::DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		Vector3 start = Matrix::ScreenChange(segment.origin, worldViewProjectionMatrix, viewportMatrix);
		Vector3 end = Matrix::ScreenChange(Vector::Add(segment.origin, segment.diff), worldViewProjectionMatrix, viewportMatrix);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		DrawSet::DrawSphere(pointSphere, worldViewProjectionMatrix, viewportMatrix, RED);
		DrawSet::DrawSphere(closestPointSphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

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
