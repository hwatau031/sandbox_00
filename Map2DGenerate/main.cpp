// 経路探索.

#include "CWindow.h"
#include "CMap.h"

void main()
{
	auto pWin =  CWindow::GetInstance();

	bool flg = pWin->CreateGameWindow( "game", 250, 250 );
	if( flg == false ){ return; }	// ウィンドウ作成失敗.
	
	CMap map;
	map.SetData();
	map.DrawMap();

	while( !pWin->IsClosed() ){
		pWin->Run();

		if( pWin->isKeyDown( VK_RETURN ) ){
			map.DebugDisp();
		}

		//メッセージキューにある全てのwindowsイベントを処理する。
		pWin->DoEvents();
	}
}

