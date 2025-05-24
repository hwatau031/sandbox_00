//======================================================================================
//	file  CWindow.cpp
//	brief CWindow
//	date  2014/06/19
//	note  
//		2025/05/24 : C++14に合わせてビルドエラー修正
//======================================================================================
#include "CWindow.h"
#include <string>
#include <locale>    // std::wstring_convert のために必要 (C++17で非推奨)
#include <codecvt>   // std::wstring_convert のために必要 (C++17で非推奨)

// C++17 以降で推奨される方法 (MultiByteToWideChar を使用)
std::wstring string_to_wstring(const std::string& str) {
    if (str.empty()) {
        return std::wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// コンストラクタ.
CWindow::CWindow()
	:m_hWnd(NULL)
	,m_KeyTbl()
{
}

// デストラクタ.
CWindow::~CWindow()
{
}

bool CWindow::CreateGameWindow( const std::string& _name, int _width, int _height )
{
    std::wstring class_name = string_to_wstring(_name);
    const DWORD style = WS_OVERLAPPEDWINDOW & ~( WS_MAXIMIZEBOX | WS_THICKFRAME );
    const DWORD exstyle = 0;//WS_EX_COMPOSITED;	// 自動的にダブルバッファリングを行う.
    const HINSTANCE instance = ::GetModuleHandle( nullptr );

    //ウィンドウクラスの登録
    WNDCLASSEX wc = { sizeof( WNDCLASSEX ) };
    wc.hInstance = instance;
    wc.lpszClassName = class_name.c_str();
    wc.lpfnWndProc = DefWindowProc;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.hIcon = static_cast< HICON >(
        ::LoadImage( nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED )
        );
    wc.hIconSm = wc.hIcon;
    wc.hCursor = static_cast< HCURSOR >(
        ::LoadImage( nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED )
        );
    wc.hbrBackground = static_cast< HBRUSH >(
        ::GetStockObject( BLACK_BRUSH )
        );
    if( !::RegisterClassEx( &wc ) ) return false;

    //クライアントサイズからウィンドウサイズを計算
    RECT rect = { 0, 0, _width, _height };
    ::AdjustWindowRectEx( &rect, style, FALSE, exstyle );

    //ウィンドウ生成
    m_hWnd = ::CreateWindowEx(
        exstyle, class_name.c_str(), class_name.c_str(), style,
        CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, instance, nullptr 
        );
    if( m_hWnd == nullptr )return false;
    ::ShowWindow( m_hWnd, SW_SHOW );

	return true;
}

bool CWindow::DoEvents()
{
	MSG msg;
    for(;;)
    {
        if( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if( msg.message == WM_QUIT )return false;

            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );        //ウィンドウプロシージャの呼び出し
        }
        else
        {
            //１フレームの処理を行うためにゲームループへ処理を戻す
            return true;
        }
    }
}

bool keyflg = true;
// 更新.
void CWindow::Run(){
	UpdateWindow( GetHandle() );

	memset( m_KeyTbl, 0, sizeof( m_KeyTbl ) / sizeof(m_KeyTbl[0]) );
	GetKeyboardState(m_KeyTbl);

	if ( !( m_KeyTbl[VK_RETURN] & 0x80 ) )
	{
		keyflg = true;
	}

	if ( isKeyDown( VK_ESCAPE ) )
	{
		DestroyWindow( GetHandle() );
	}
};

int CWindow::isKeyDown( BYTE _key )
{
	if( _key == VK_RETURN ){ 
		if( !keyflg ) return 0; 

		keyflg = !( m_KeyTbl[_key] & 0x80 );
	}
	return ( m_KeyTbl[_key] & 0x80 );
}

// 表示.
void CWindow::Draw()
{
	InvalidateRect( GetHandle() , NULL , FALSE );
};

