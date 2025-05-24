#include "CWindow.h"
#include <chrono> // 時間測定に必要

int main()
{
	// 1秒間に60回 (60 FPS) を目標とする
	const double target_fps = 60.0;

	// frame_duration_target を std::chrono::microseconds (マイクロ秒) で定義
	const std::chrono::microseconds frame_duration_target =
		std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::duration<double>(1.0 / target_fps) );

	// 次のフレームを開始すべき時刻
	std::chrono::steady_clock::time_point next_frame_time = std::chrono::steady_clock::now();

	auto pWin =  CWindow::GetInstance();

	bool flg = pWin->CreateGameWindow("game", 720, 480);
	if( flg == false ){ return 0; }	// ウィンドウ作成失敗.

	while (!pWin->IsClosed())
	{
		// --- ここからフレームごとの処理 ---
		{
			// 塗りつぶし
			pWin->DrawRectangle(0, 0, 720, 480, BLACK_BRUSH);

			pWin->Run();

			// テスト用
			{
				static int cnt = 0;
				static int x = 0;
				cnt++;
				if (cnt > 10)
				{
					cnt = 0;
					x += 10;
				}
				pWin->DrawRectangle(x, 100, 10, 10, WHITE_BRUSH);
			}

			//メッセージキューにある全てのwindowsイベントを処理する。
			pWin->DoEvents();
		}
		// --- フレームごとの処理ここまで ---

		// 次のフレーム開始時刻まで待機 (ビジーループ)
		while (std::chrono::high_resolution_clock::now() < next_frame_time) {
			// 何もしないでループし続ける
			// 必要であれば、ここで非常に短いスリープ (例: std::this_thread::yield()) を入れると
			// CPU使用率をわずかに抑えられる可能性がありますが、保証はありません。
			// std::this_thread::yield(); // OSに他のスレッドにCPUを譲るようにヒントを与える
		}

		// 次のフレームの開始時刻を計算
		// 処理にかかった時間を考慮せず、単純に目標フレーム時間を加算していく方法
		next_frame_time += frame_duration_target;

		// もし処理が遅れて、次のフレームの開始時刻が現在時刻よりも過去になってしまった場合、
		// 追いつくために次のフレームの開始時刻を現在時刻に調整する (フレームスキップ/カクつき防止)
		if (next_frame_time < std::chrono::high_resolution_clock::now()) {
			next_frame_time = std::chrono::high_resolution_clock::now();
		}
	}

	return 0;
}

