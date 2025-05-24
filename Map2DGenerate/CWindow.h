//======================================================================================
//	file CWindow.h
//	brif CWindow
//	date 2014/06/19
//	note 
//		2025/05/24 : C++14に合わせてビルドエラー修正
//======================================================================================

#ifndef __CWINDOW_H__
#define __CWINDOW_H__

#include <string>
#include <windows.h>
#include "CSingletonBase.h"

class CWindow : public CSingletonBase<CWindow>
{
public:
	// コンストラクタ.
	CWindow();
	// デストラクタ.
	virtual ~CWindow();

public:
	// ウィンドウ作成.
	bool CreateGameWindow( const std::string& _name = "game", int _width = 720, int _height = 480 );
	// ハンドル取得.
	inline HWND GetHandle(){ return m_hWnd; }
	//ウィンドウが閉じられたか
	inline bool IsClosed(){ return ::IsWindow( m_hWnd ) == FALSE; }

	// windowsイベントがあればプロシージャを実行する。
	// @return WM_QUITメッセージを受け取ったかどうか
	bool DoEvents();
	// 更新.
	void Run();
	// 表示.
	void Draw();

	int isKeyDown( BYTE _key );

private:
	HWND m_hWnd;	// ウィンドウハンドル.
	BYTE m_KeyTbl[256];
};

#endif // __CWINDOW_H__

