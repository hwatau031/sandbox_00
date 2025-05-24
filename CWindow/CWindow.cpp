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
{
}

// デストラクタ.
CWindow::~CWindow()
{
}

bool CWindow::CreateGameWindow( const std::string& name, int width, int height )
{
    std::wstring class_name = string_to_wstring(name);
    const DWORD style = WS_OVERLAPPEDWINDOW & ~( WS_MAXIMIZEBOX | WS_THICKFRAME );
    const DWORD exstyle = 0;
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
        ::GetStockObject( WHITE_BRUSH )
        );
    if( !::RegisterClassEx( &wc ) ) return false;

    //クライアントサイズからウィンドウサイズを計算
    RECT rect = { 0, 0, width, height };
    ::AdjustWindowRectEx( &rect, style, FALSE, exstyle );

    //ウィンドウ生成
    m_hWnd = ::CreateWindowEx(
        exstyle, class_name.c_str(), class_name.c_str(), style,
        CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, instance, nullptr 
        );
    if( m_hWnd == nullptr ) return false;
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
            // ウィンドウプロシージャの呼び出し
            ::DispatchMessage( &msg );
        }
        else
        {
            // 1フレームの処理を行うためにゲームループへ処理を戻す
            return true;
        }
    }
}

// 更新
void CWindow::Run()
{
	UpdateWindow( GetHandle() );

	BYTE KeyTbl[256];
    if (isKeyDown(VK_ESCAPE))
    {
        DestroyWindow(GetHandle());
    }
};

// 表示.
void CWindow::DrawRectangle(int x, int y, int w, int h, int brush)
{
	InvalidateRect( GetHandle() , NULL , FALSE );

	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint( GetHandle() , &ps );

	SelectObject( hdc , GetStockObject( brush ) );
	Rectangle( hdc , x, y, x+w, y+h );

	EndPaint( GetHandle() , &ps );
};

