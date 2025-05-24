//======================================================================================
//	file  CMap.cpp
//	brief CMap
//	date  2014/06/19
//	note  
//	
//======================================================================================

#include <time.h>
#include "CMap.h"
#include "CWindow.h"
#include "CRandomMap.h"

#define COLOR_RED		RGB( 255, 0, 0 )
#define COLOR_GREEN		RGB( 0, 255, 0 )
#define COLOR_BLUE		RGB( 0, 0, 255 )
#define COLOR_BLACK		RGB( 0, 0, 0 )
#define COLOR_CYAN		RGB( 0, 255, 255 )
#define COLOR_YELLOW	RGB( 255, 255, 0 )
#define COLOR_MAGENTA	RGB( 255, 0, 255 )

#define PANEL_PONT(x) SPos( x, PANEL_SIZE / 2, PANEL_SIZE / 2 )

// コンストラクタ.
CMap::CMap():m_MapParam()
{
	m_pRandomMap = new CRandomMap;
}

// デストラクタ.
CMap::~CMap()
{
	if( m_pRandomMap ) delete m_pRandomMap;
}


void CMap::SetData()
{
	// スタートが置けるパーツだけのリストを作る.
	std::vector<SMapdata*> startPartsList;
	do{
		m_pRandomMap->SetStartPos();
		m_pRandomMap->GetMapPartsList( startPartsList );
	}while( startPartsList.size() == 0 );

	// スタートがどのパーツの位置か判定.
	SPos* pStartPos = m_pRandomMap->GetStartPos();
	const int baseIdx_x = ( pStartPos->x / 5 ) * 5;
	const int baseIdx_y = ( pStartPos->y / 5 ) * 5;

	// スタートが置けるパーツを配置.
	int rnd = rand() % startPartsList.size();
	SMapdata* data = startPartsList[ rnd ];
	SetMapParts( data, baseIdx_x, baseIdx_y );

	// スタートを配置.
	m_MapParam[pStartPos->y][pStartPos->x].panel = 2;
	printf( "start( %d, %d )\n", pStartPos->x, pStartPos->y );
	
	SetMapPartsAll( baseIdx_x, baseIdx_y );
}

// 接続できる方向を判定.
int CMap::CheckInstDirFromPos( int _partsIdx_x, int _partsIdx_y )
{
	int dirBit = 0;
	{
		int idx_x = _partsIdx_x + 2, idx_y = _partsIdx_y;
		if( m_MapParam[idx_y][idx_x].panel > 0 /*&& ( WALL_CHECK_BTM( m_MapParam[idx_y][idx_x].wall ) == false )*/ )
			if( m_MapParam[idx_y-1][idx_x].panel == 0 ) dirBit |= ECheckInst_Top;
	}{
		int idx_x = _partsIdx_x + 2, idx_y = _partsIdx_y + 4;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			if( m_MapParam[idx_y+1][idx_x].panel == 0 ) dirBit |= ECheckInst_Btm;
	}{
		int idx_x = _partsIdx_x, idx_y = _partsIdx_y + 2;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			if( m_MapParam[idx_y][idx_x-1].panel == 0 ) dirBit |= ECheckInst_Left;
	}{	
		int idx_x = _partsIdx_x + 4, idx_y = _partsIdx_y + 2;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			if( m_MapParam[idx_y][idx_x+1].panel == 0 ) dirBit |= ECheckInst_Right;
	}

	return dirBit;
}

// 指定座標の周囲4方向の領域を判定.
int CMap::CheckNextInstDirFromPos( int _partsIdx_x, int _partsIdx_y )
{
	int dirBit = 0;
	{
		int idx_x = _partsIdx_x + 2, idx_y = _partsIdx_y - 1;
		if( m_MapParam[idx_y][idx_x].panel > 0 /*&& ( WALL_CHECK_BTM( m_MapParam[idx_y][idx_x].wall ) == false )*/ )
			dirBit |= ECheckInst_Top;
	}{
		int idx_x = _partsIdx_x + 2, idx_y = _partsIdx_y + 5;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			dirBit |= ECheckInst_Btm;
	}{
		int idx_x = _partsIdx_x - 1, idx_y = _partsIdx_y + 2;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			dirBit |= ECheckInst_Left;
	}{	
		int idx_x = _partsIdx_x + 5, idx_y = _partsIdx_y + 2;
		if( m_MapParam[idx_y][idx_x].panel > 0 )
			dirBit |= ECheckInst_Right;
	}

	return dirBit;
}

void CMap::SetMapParts( SMapdata* _data, int idx_x, int idx_y )
{
	if( !_data ) return;

	for( int ii = 0; ii < 5; ii++ ){
		for( int jj= 0; jj < 5; jj++ ){
			m_MapParam[ii+idx_y][jj+idx_x].panel = _data->panel[ii][jj];
			m_MapParam[ii+idx_y][jj+idx_x].wall = _data->wall[ii][jj];
		}
	}
}

void CMap::SetMapParts( int idx_x, int idx_y, int _posBit )
{
	std::vector<SMapdata*> partsList;
	m_pRandomMap->GetMapPartsList( partsList, _posBit );

	int rnd = rand() % partsList.size();
	SMapdata* data = partsList[ rnd ];
	SetMapParts( data, idx_x, idx_y );

//	printf("配置 ( %d, %d )\n", idx_x, idx_y );
}

void CMap::SetMapPartsAll( int idx_x, int idx_y )
{
	//4.配置したパーツがどの方向に繋げられるかチェック.
	int partsDirBit = CheckInstDirFromPos( idx_x, idx_y );
	//5.繋がる先でさらに4方向をチェック.
	//	4方向のどこかにすでに配置されているパーツがあればその方向にも繋げられるパーツしか置けない.
	//6.(4)(5)の条件に当てはまるパーツを配置.
	//	マップ端に配置する場合はこの段階で先に繋げられるパーツをはじくか、繋がる部分に壁を作る.
	//7.配置できるところがなくなるまで(4)～(6)を繰り返す.
	//8.ゴールを配置.

	if( idx_y >= 5 && partsDirBit & ECheckInst_Top ){
		int y = idx_y - 5;
		int posDirBit = CheckNextInstDirFromPos( idx_x, y );
		SetMapParts( idx_x, y, posDirBit );
		SetMapPartsAll( idx_x, y );	
	}
	if( idx_y < 20 && partsDirBit & ECheckInst_Btm ){
		int y = idx_y + 5;
		int posDirBit = CheckNextInstDirFromPos( idx_x, y );
		SetMapParts( idx_x, y, posDirBit );
		SetMapPartsAll( idx_x, y );
	}
	if( idx_x >= 5 && partsDirBit & ECheckInst_Left ){
		int x = idx_x - 5;
		int posDirBit = CheckNextInstDirFromPos( x, idx_y );
		SetMapParts( x, idx_y, posDirBit );
		SetMapPartsAll( x, idx_y );
	}
	if( idx_x < 20 && partsDirBit & ECheckInst_Right ){
		int x = idx_x + 5;
		int posDirBit = CheckNextInstDirFromPos( x, idx_y );
		SetMapParts( x, idx_y, posDirBit );
		SetMapPartsAll( x, idx_y );
	}
}

void CMap::DrawMap()
{
	for( int ii = 0; ii < 25; ii++ ){
		for( int jj= 0; jj < 25; jj++ ){
			int x = ( PANEL_SIZE * jj ) + 10;
			int y = ( PANEL_SIZE * ii ) + 10;
			int brush = 0;
			if( m_MapParam[ii][jj].panel ){
				brush = ( m_MapParam[ii][jj].panel == 1 ) ? WHITE_BRUSH : GRAY_BRUSH;
			}else{
				brush = DKGRAY_BRUSH;
			}
			DrawRect( SPos( ii, jj ), brush );
			DrawWall( m_MapParam[ii][jj].wall, SPos( ii, jj ) );
		}
	}
}

void CMap::DrawWall( unsigned int wall, SPos pos )
{
	if( wall & ( 1 << 0 ) ) DrawLine( pos, SPos( pos, PANEL_SIZE, 0 ) );	// 上.
	if( wall & ( 1 << 1 ) ) DrawLine( SPos( pos, 0, PANEL_SIZE ), SPos( pos, PANEL_SIZE, PANEL_SIZE ) );	// 下.
	if( wall & ( 1 << 2 ) ) DrawLine( pos, SPos( pos, 0, PANEL_SIZE ) );	// 左.
	if( wall & ( 1 << 3 ) ) DrawLine( SPos( pos, PANEL_SIZE, 0 ), SPos( pos, PANEL_SIZE, PANEL_SIZE ) );	// 右.
}

void CMap::DrawPoint( SPos pos, COLORREF color )
{
	HWND hWnd = CWindow::GetInstance()->GetHandle();
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;

	CWindow::GetInstance()->Draw();
	hdc = BeginPaint( hWnd , &ps );

	hPen = CreatePen( PS_SOLID, 5, color );
	hPen = (HPEN)SelectObject( hdc, hPen ); /* ペンの設定 */

	MoveToEx( hdc, pos.x, pos.y, NULL ); // 始点.
	LineTo( hdc, pos.x, pos.y );	// 終点.

	EndPaint( hWnd , &ps );
}

void CMap::DrawLine( SPos pos, SPos pos2, int width, COLORREF color )
{
	HWND hWnd = CWindow::GetInstance()->GetHandle();
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;

	CWindow::GetInstance()->Draw();
	hdc = BeginPaint( hWnd , &ps );

	hPen = CreatePen( PS_SOLID, width, color );
	hPen = (HPEN)SelectObject( hdc, hPen ); /* ペンの設定 */

	MoveToEx( hdc, pos.x, pos.y, NULL ); // 始点.
	LineTo( hdc, pos2.x, pos2.y );	// 終点.

//	SelectObject(hdc, hPen);

	EndPaint( hWnd , &ps );
}

void CMap::DrawRect( SPos pos, int brush )
{
	HWND hWnd = CWindow::GetInstance()->GetHandle();
	HDC hdc;
	PAINTSTRUCT ps;

	CWindow::GetInstance()->Draw();
	hdc = BeginPaint( hWnd , &ps );
	
	SelectObject( hdc , GetStockObject( brush ) );
	Rectangle( hdc , pos.x , pos.y , pos.x + PANEL_SIZE , pos.y + PANEL_SIZE );

	EndPaint( hWnd , &ps );
}


void CMap::DebugDisp()
{
	InvalidateRect( CWindow::GetInstance()->GetHandle() , NULL , TRUE );
	DrawMap();
}