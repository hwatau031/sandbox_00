//======================================================================================
//	file  CRouteSearch.cpp
//	brief CRouteSearch
//	date  2014/06/20
//	note  
//	
//======================================================================================

#include "CRouteSearch.h"

// コンストラクタ.
CRouteSearch::CRouteSearch()
	:start(NULL)
	,goal(NULL)
{
}

// デストラクタ.
CRouteSearch::~CRouteSearch()
{
	m_node.clear();
}

void CRouteSearch::setNode( SPos _pos )
{
	m_node.push_back( new Node( _pos )  );
}

void CRouteSearch::SetStart( SPos _pos )
{
	start = Query( _pos );
	if( start == NULL ){
		setNode( _pos );
		start = Query( _pos );
	}
}

void CRouteSearch::SetGoal( SPos _pos )
{
	goal = Query( _pos );
	if( goal == NULL ){
		setNode( _pos );
		goal = Query( _pos );
	}
}

bool isGoal = true;	// デバッグ用
void CRouteSearch::SearchRoot()
{
	static std::vector<Node*> currList;	// チェックするリスト.
	static std::vector<Node*> nextList;	// 次にチェックするリスト.

	if( isGoal ){
		// 距離をリセット.
		for( auto it = m_node.begin(); it != m_node.end(); it++ ){
			(*it)->cost = -1;
			(*it)->toGoal = NULL;
		}
		
		Node* st = goal;
		if( st ){
			st->cost = 0;
			currList.push_back( st );
		}

		isGoal = false;
	}

//	while( currList.size() )
	{
		int nodeCost = 0;
		for( auto it = currList.begin(); it != currList.end(); it++  ){		
			for( auto connect = (*it)->m_connectNode.begin(); connect != (*it)->m_connectNode.end(); connect++ ) {
				// 次のノードまでの合計コスト.
				nodeCost = (*it)->cost + connect->cost;

				// 未探索か最短ルートを更新できる場合.
				if( connect->node->cost < 0 || nodeCost < connect->node->cost ){
					connect->node->checknow = true;

					// コストとルートをセット.
					connect->node->cost = nodeCost;
					connect->node->toGoal = (*it);

					// 次のリストに追加.
					nextList.push_back( connect->node );
				}
			}

			(*it)->checknow = false;
		}

		// リスト入れ替え.
		currList.swap( nextList );
		nextList.clear();
	}

	if( currList.size() <= 0 ) isGoal = true;
}

Node* CRouteSearch::Query( SPos _pos )
{
	for ( auto it = m_node.begin(); it != m_node.end(); it++ ) {
		if( (*it)->pos == _pos ){
			return (*it);
		}
	
	}
	return NULL;
}