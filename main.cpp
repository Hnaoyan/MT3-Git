#include <Novice.h>
#include"Matrix.h"

const char kWindowTitle[] = "学籍番号";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

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
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix4x4 m1 =
	{
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	};

	Matrix4x4 m2 =
	{
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	Matrix* matrix = new Matrix();

	Matrix4x4 resultAdd = matrix->Add(m1, m2);// 加法
	Matrix4x4 resultMultiply = matrix->Multiply(m1, m2);
	Matrix4x4 resultSubtract = matrix->Subtract(m1, m2);
	Matrix4x4 inverseM1 = matrix->Inverse(m1);
	Matrix4x4 inverseM2 = matrix->Inverse(m2);
	Matrix4x4 transposeM1 = matrix->Transpose(m1);
	Matrix4x4 transposeM2 = matrix->Transpose(m2);
	Matrix4x4 identity = matrix->MakeIdentity4x4();

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

		MatrixScreenPrintf(int(0), int(0), resultAdd, "Add");
		MatrixScreenPrintf(int(0), int(kRowHeight * 5), resultSubtract, "Subtract");
		MatrixScreenPrintf(int(0), int(kRowHeight * 5 * 2), resultMultiply, "Multiply");
		MatrixScreenPrintf(int(0), int(kRowHeight * 5 * 3), inverseM1, "inverseM1");
		MatrixScreenPrintf(int(0), int(kRowHeight * 5 * 4), inverseM2, "inverseM2");
		MatrixScreenPrintf(int(kColumnWidth * 5), 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(int(kColumnWidth * 5), int(kRowHeight * 5), transposeM2, "transposeM2");
		MatrixScreenPrintf(int(kColumnWidth * 5), int(kRowHeight * 5 * 2), identity, "identity");


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			delete matrix;
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
