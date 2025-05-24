//======================================================================================
//	file CWindow.h
//	brif CWindow
//	date 2014/06/19
//	note 
//		2025/05/24 : C++14に合わせてビルドエラー修正
//======================================================================================

#pragma once
#include <string>
#include "CSingletonBase.h"
#include "CKeyboard.h"

class CWindow : public CSingletonBase<CWindow>, CKeyboard
{
public:
	// コンストラクタ.
	CWindow();
	// デストラクタ.
	virtual ~CWindow();

public:
	// ウィンドウ作成.
	bool CreateGameWindow( const std::string& name, int width, int height );
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
	void DrawRectangle(int x, int y, int w, int h, int brush);

private:
	HWND m_hWnd;	// ウィンドウハンドル.
};

