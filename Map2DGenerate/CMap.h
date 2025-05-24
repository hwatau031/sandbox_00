//======================================================================================
//	file CMap.h
//	brif CMap
//	date 2014/06/19
//	note 
// 
//======================================================================================

#ifndef __CMAP_H__
#define __CMAP_H__

#include <windows.h>
//#include "CRouteSearch.h"
#include "CRandomMap.h"

class CRandomMap;

enum eObjtype{
	eObjtype_None = 0,	// なし.
	eObjtype_Trap,		// トラップ.
	eObjtype_Item,		// 宝箱.
};

// 地面は1なら通れる( 2がスタート ).
// 壁は上下左右でビット判定.
struct SMapParam
{
	unsigned char panel;	// 地面タイプ.
	unsigned char wall;		// 壁.
	unsigned char object;	// オブジェクト.
};

struct SPos;

class CMap// : public CRouteSearch
{
public:
	// コンストラクタ.
	CMap();
	// デストラクタ.
	virtual ~CMap();

	void SetData();
	// 配置できる方向を調べる.
	int CheckInstDirFromPos( int _partsIdx_x, int _partsIdx_y );
	int CheckNextInstDirFromPos( int _partsIdx_x, int _partsIdx_y );
	void SetMapParts( SMapdata* _data, int idx_x, int idx_y );
	void SetMapParts( int idx_x, int idx_y, int _posBit );
	void SetMapPartsAll( int idx_x, int idx_y );
	void GetMapPartsList( std::vector<SMapdata*>& _v, ECheckInst _type );
	void DrawMap();
	void DrawWall( unsigned int wall, SPos pos );

	void DrawPoint( SPos pos, COLORREF color );
	void DrawLine( SPos pos, SPos pos2, int width = 2, COLORREF color = RGB( 255, 0, 0 ) );
	void DrawRect( SPos pos, int brush );
	
	// ノードの接続チェック.
	bool isNodeConnectOk( Node* _from, Node* _to );
	// 指定座標に近いノードを取得.
	Node* GetNearNode( SPos _pos );

	void DrawNode();

	void DebugDisp();
	void DispRoot( Node* _pNode );

private:
	SMapParam m_MapParam[25][25];
	CRandomMap* m_pRandomMap;
};

#endif // __CMAP_H__

