//======================================================================================
//	file CRandomMap.h
//	brif CRandomMap
//	date 2014/06/25
//	note 
// 
//======================================================================================

#ifndef __CRANDOMMAP_H__
#define __CRANDOMMAP_H__

#include <vector>

#include "CRouteSearch.h"

#define MAP_PRTS_SIZE_X ( 5 )
#define MAP_PRTS_SIZE_Y ( 5 )

#define WALL_CHECK_TOP( _wall_ ) ( _wall_ & ( 1 << 0 ) )
#define WALL_CHECK_BTM( _wall_ ) ( _wall_ & ( 1 << 1 ) )
#define WALL_CHECK_LEFT( _wall_ ) ( _wall_ & ( 1 << 2 ) )
#define WALL_CHECK_RIGHT( _wall_ ) ( _wall_ & ( 1 << 3 ) )

struct SMapdata{
	SMapdata(){};
	SMapdata( unsigned char paneldata[MAP_PRTS_SIZE_Y][MAP_PRTS_SIZE_X], unsigned char walldata[MAP_PRTS_SIZE_Y][MAP_PRTS_SIZE_X] ){
		memcpy( panel, paneldata, sizeof( panel ) );
		memcpy( wall, walldata, sizeof( wall ) );
	}

	unsigned char panel[MAP_PRTS_SIZE_Y][MAP_PRTS_SIZE_X];
	unsigned char wall[MAP_PRTS_SIZE_Y][MAP_PRTS_SIZE_X];
};

// 配置チェックタイプ.
enum ECheckInst{
	ECheckInst_None		= 0,
	ECheckInst_Start	= ( 1 << 0 ),
	ECheckInst_Top		= ( 1 << 1 ),
	ECheckInst_Btm		= ( 1 << 2 ),
	ECheckInst_Left		= ( 1 << 3 ),
	ECheckInst_Right	= ( 1 << 4 ),
};

class CRandomMap
{
public:
	// コンストラクタ.
	CRandomMap();
	// デストラクタ.
	virtual ~CRandomMap();

	void SetStartPos();
	SPos* GetStartPos(){ return &m_startPos; }
	std::vector<SMapdata>* GetMapPartsList(){ return &m_MapParts; }
	
	bool CheckInst( SMapdata* _data, ECheckInst _dir );
	// パーツから設置できる方向を取得.
	int  GetInstDir( SMapdata* _data );

	void GetMapPartsList( std::vector<SMapdata*>& _v, int _posDir = 0 );

private:
	void LoadMapPartsData();

private:
	std::vector<SMapdata> m_MapParts;
	SPos m_startPos;
};

#endif // __CRANDOMMAP_H__

