//======================================================================================
//	file  CRandomMap.cpp
//	brief CRandomMap
//	date  2014/06/25
//	note  
//	
//======================================================================================
/*
1.スタートの位置をランダムで決める.
2.スタートがどのパーツの位置なのか判定.
3.スタートが置けるパーツを配置.
4.配置したパーツがどの方向に繋げられるかチェック.
5.繋がる先でさらに4方向をチェック.
	4方向のどこかにすでに配置されているパーツがあればその方向にも繋げられるパーツしか置けない.
6.(4)(5)の条件に当てはまるパーツを配置.
	マップ端に配置する場合はこの段階で先に繋げられるパーツをはじくか、繋がる部分に壁を作る.
7.配置できるところがなくなるまで(4)～(6)を繰り返す.
8.ゴールを配置.


****************
マップ端の判定は面倒なのでスルー.
今のままだと極端に短いマップもできるのでその辺も考えないとだめかも.
*/
#include  <time.h>
#include "CRandomMap.h"
#include "Mapdata.h"

// コンストラクタ.
CRandomMap::CRandomMap()
{
	LoadMapPartsData();

	srand(time(NULL));                        /* 現在の時刻から種を決定 */
}

// デストラクタ.
CRandomMap::~CRandomMap()
{
}

void CRandomMap::SetStartPos()
{
	// スタートの位置をランダムに決める.
	m_startPos.x = rand() % 25;
	m_startPos.y = rand() % 25;
}

bool CRandomMap::CheckInst( SMapdata* _data, ECheckInst _dir )
{
	switch( _dir ){
	case ECheckInst_Top:
		return ( _data->panel[0][2] > 0 );

	case ECheckInst_Btm:
		return ( _data->panel[4][2] > 0 );

	case ECheckInst_Left:
		return ( _data->panel[2][0] > 0 );

	case ECheckInst_Right:
		return ( _data->panel[2][4] > 0 );
	}

	return false;
}

// パーツから設置できる方向を取得.
int CRandomMap::GetInstDir( SMapdata* _data )
{
	int dirBit = 0;

	if( _data->panel[0][2] > 0 ) dirBit |= ECheckInst_Top;
	if( _data->panel[4][2] > 0 ) dirBit |= ECheckInst_Btm;
	if( _data->panel[2][0] > 0 ) dirBit |= ECheckInst_Left;
	if( _data->panel[2][4] > 0 ) dirBit |= ECheckInst_Right;

	return dirBit;
}

// 指定した方向に繋げられるパーツのリストを取得.
void CRandomMap::GetMapPartsList( std::vector<SMapdata*>& _v, int _posDir )
{
	const auto pPartsList = GetMapPartsList();

	if( _posDir == 0 ){
		for( auto it = (*pPartsList).begin(); it != (*pPartsList).end(); it++ ){
			// スタートの位置がただの通路ならOK.
			SPos* pStartPos = GetStartPos();
			int idx_x = pStartPos->x - ( ( pStartPos->x / 5 ) * 5 );
			int idx_y = pStartPos->y - ( ( pStartPos->y / 5 ) * 5 );

			if( it->panel[ idx_y ][ idx_x ] == 1 ){
				_v.push_back( it._Ptr );
			}
		}
	}else{
		for( auto it = (*pPartsList).begin(); it != (*pPartsList).end(); it++ ){
			// 繋げられる道があるならその方向につながるパーツじゃないとだめ.
			if( _posDir & ECheckInst_Top )	{ if( !CheckInst( it._Ptr, ECheckInst_Top ) )	continue; }
			if( _posDir & ECheckInst_Btm )	{ if( !CheckInst( it._Ptr, ECheckInst_Btm ) )	continue; }
			if( _posDir & ECheckInst_Left )	{ if( !CheckInst( it._Ptr, ECheckInst_Left ) )	continue; }
			if( _posDir & ECheckInst_Right ){ if( !CheckInst( it._Ptr, ECheckInst_Right ) ) continue; }

			_v.push_back( it._Ptr );
		}
	}
}

void CRandomMap::LoadMapPartsData()
{
	for( int ii = 0; ii < sizeof( paneldata ) / sizeof( paneldata[0] ); ii++ ){
		m_MapParts.push_back( SMapdata( paneldata[ii], walldata[ii] ) );
	}
}