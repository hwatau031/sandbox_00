//======================================================================================
//	file CRouteSearch.h
//	brif CRouteSearch
//	date 2014/06/20
//	note 
// 
//======================================================================================

#ifndef __CROUTESEARCH_H__
#define __CROUTESEARCH_H__

#include <vector>

#define PANEL_SIZE ( 20/2 )

struct SPos{
	SPos():x(0),y(0){};
	SPos( int _idx_ii, int _idx_jj )
	{
		x = ( PANEL_SIZE * _idx_jj );
		y = ( PANEL_SIZE * _idx_ii );
	};
	SPos( SPos pos, int ofs_x, int ofs_y )
	{
		x = pos.x + ofs_x;
		y = pos.y + ofs_y;
	}
	SPos( int _idx_ii, int _idx_jj, int ofs_x, int ofs_y )
	{
		x = ( PANEL_SIZE * _idx_jj ) + ofs_x;
		y = ( PANEL_SIZE * _idx_ii ) + ofs_y;
	}

	bool operator == ( SPos _pos )
	{
		return ( x == _pos.x && y == _pos.y );
	}

	int operator - ( SPos _pos )
	{
		return ( x - _pos.x ) + ( y - _pos.y );
	}

	int x;
	int y;
};

// ノードのパラメータ.
enum eNodeParam{
	eNodeParam_None = 0,	// なし.
	eNodeParam_Trap,		// 罠.
	eNodeParam_Item,		// 宝箱.
	eNodeParam_Item2,		// 採取.
};

struct Node;
struct NodeConnect;

//ノード
struct Node {
	Node( SPos _pos, eNodeParam _param = eNodeParam_None )
		:cost(0),toGoal(NULL), pos(_pos), param(_param)
		, checknow(false), num(0)
	{
		static int number = 0;
		num = number++;
	}

	int GetDist( Node* _node ){
		int dist = ( pos - _node->pos ) / PANEL_SIZE;
		if( dist < 0 ) dist *= -1;
		return dist;
	}

    std::vector<NodeConnect> m_connectNode;  //接続しているノード
    int	  cost;   //探索に要したコスト。-1の時はそのノードを未探索としています。
    Node* toGoal; //ゴールへの最短ルートにつながるノード

	eNodeParam param;
	SPos pos;

	// デバッグ用パラメータ.
	bool checknow;
	int  num;
};

//他のノードへの接続情報
struct NodeConnect {
    Node*  node;//移動先ノード
    int    cost;//移動にかかるコスト

	NodeConnect( Node*	_node, int _cost )
	{
		node = _node;
		cost = _cost;
	}
};

class CRouteSearch
{
public:
	// コンストラクタ.
	CRouteSearch();
	// デストラクタ.
	virtual ~CRouteSearch();

	void setNode( SPos pos );
	void SetStart( SPos pos );
	void SetGoal( SPos pos );
	void SearchRoot();

	// 座標からノードを取得
	Node* Query( SPos _pos );

	// ※マップ情報が判定に必要なのでここでは定義しない.
	// ノードの接続チェック.
	virtual bool isNodeConnectOk( Node* _from, Node* _to ) = 0;
	// 指定座標に近いノードを取得.
	virtual Node* GetNearNode( SPos _pos ) = 0;

protected:
	Node* start;
	Node* goal;
	std::vector<Node*> m_node;
};

#endif // __CROUTESEARCH_H__

