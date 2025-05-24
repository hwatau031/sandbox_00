//======================================================================================
//	file Mapdata.h
//	brif Mapdata
//	date 2014/06/19
//	note 
//		マップデータ
//		形式は俺働風.
// 
//======================================================================================

#ifndef __MAPDATA_H__
#define __MAPDATA_H__
#if 1
// 地面データ.
unsigned char paneldata[][5][5] = {
		//0  1  2  3  4.
	{	// 1.
		{ 0, 0, 1, 0, 0 },	// 0.
		{ 0, 0, 1, 0, 0 },	// 1.
		{ 0, 0, 1, 0, 0 },	// 2.
		{ 0, 0, 1, 0, 0 },	// 3.
		{ 0, 0, 1, 0, 0 },	// 4.	
	},{	// 2.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 1, 1, 1 },	// 2.
		{ 0, 0, 1, 0, 0 },	// 3.
		{ 0, 0, 1, 0, 0 },	// 4.	
	},{	// 3.
		{ 0, 0, 1, 0, 0 },	// 0.
		{ 0, 1, 1, 1, 0 },	// 1.
		{ 1, 1, 1, 1, 1 },	// 2.
		{ 0, 1, 1, 1, 0 },	// 3.
		{ 0, 0, 1, 0, 0 },	// 4.	
	},{	// 4.
		{ 0, 0, 1, 0, 0 },	// 0.
		{ 0, 0, 1, 0, 0 },	// 1.
		{ 1, 1, 1, 0, 1 },	// 2.
		{ 0, 0, 1, 1, 1 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 5.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 1, 0, 0 },	// 2.
		{ 0, 0, 1, 0, 0 },	// 3.
		{ 0, 0, 1, 0, 0 },	// 4.	
	},{	// 6.
		{ 0, 0, 1, 0, 0 },	// 0.
		{ 0, 0, 1, 0, 0 },	// 1.
		{ 0, 0, 1, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 7.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 1, 1, 1, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 8.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 1, 1, 1 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// .
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 0, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	}
};

// 壁.
unsigned char walldata[][5][5] = {
		//0  1  2  3  4.
	{	// 1.
		{ 0, 0,12, 0, 0 },	// 0.
		{ 0, 0,12, 0, 0 },	// 1.
		{ 0, 0,12, 0, 0 },	// 2.
		{ 0, 0,12, 0, 0 },	// 3.
		{ 0, 0,12, 0, 0 },	// 4.	
	},{	// 2.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 5, 3, 3 },	// 2.
		{ 0, 0,12, 0, 0 },	// 3.
		{ 0, 0,12, 0, 0 },	// 4.
	},{	// 3.
		{ 0, 0,12, 0, 0 },	// 0.
		{ 0, 5, 0, 9, 0 },	// 1.
		{ 3, 0, 0, 0, 3 },	// 2.
		{ 0, 6, 0,10, 0 },	// 3.
		{ 0, 0,12, 0, 0 },	// 4.	
	},{	// 4.
		{ 0, 0,12, 0, 0 },	// 0.
		{ 0, 0,12, 0, 0 },	// 1.
		{ 3, 3, 8, 0, 5 },	// 2.
		{ 0, 0, 6, 3,10 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 5.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0,13, 0, 0 },	// 2.
		{ 0, 0,12, 0, 0 },	// 3.
		{ 0, 0,12, 0, 0 },	// 4.	
	},{	// 6.
		{ 0, 0,12, 0, 0 },	// 0.
		{ 0, 0,12, 0, 0 },	// 1.
		{ 0, 0,14, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 7.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 3, 3,11, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// 8.
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 7, 3, 3 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	},{	// .
		{ 0, 0, 0, 0, 0 },	// 0.
		{ 0, 0, 0, 0, 0 },	// 1.
		{ 0, 0, 0, 0, 0 },	// 2.
		{ 0, 0, 0, 0, 0 },	// 3.
		{ 0, 0, 0, 0, 0 },	// 4.	
	}
};

#else
// 地面データ.
unsigned char paneldata[5][5] = {
	//0  1  2  3  4.
	{ 0, 0, 0, 0, 0 },		// 0.
	{ 0, 0, 0, 0, 0 },		// 1.
	{ 0, 0, 0, 0, 0 },		// 2.
	{ 0, 0, 0, 0, 0 },		// 3.
	{ 0, 0, 0, 0, 0 },		// 4.	
};

// 壁.
unsigned char walldata[5][5] = {
	//0  1  2  3  4.
	{ 0, 0, 0, 0, 0 },		// 0.
	{ 0, 0, 0, 0, 0 },		// 1.
	{ 0, 0, 0, 0, 0 },		// 2.
	{ 0, 0, 0, 0, 0 },		// 3.
	{ 0, 0, 0, 0, 0 },		// 4.	
};
#endif

bool wallcheck( unsigned char _p[][20], int _idx_ii, int _idx_jj )
{
	bool flg = false;
	if( _p[_idx_ii][_idx_jj] ){
		auto panel_top   = _p[_idx_ii][_idx_jj] & ( 1 << 0 );
		auto panel_btm   = _p[_idx_ii][_idx_jj] & ( 1 << 1 );
		auto panel_left  = _p[_idx_ii][_idx_jj] & ( 1 << 2 );
		auto panel_right = _p[_idx_ii][_idx_jj] & ( 1 << 3 );

		int count = 0;
		if( panel_top )	  count++;	
		if( panel_btm )	  count++;
		if( panel_left )  count++;
		if( panel_right ) count++;

		if( count == 2 ){
			flg = true;
		}
	}

	return flg;
}

// 上.
bool check_top( int _idx_ii, int _idx_jj )
{
//	auto panel = paneldata[_idx_ii-1][_idx_jj];
//	auto wall  = walldata[_idx_ii][_idx_jj] & ( 1 << 0 );

//	if( panel && !wall ) return true;
	return false;
}
// 下.
bool check_btm( int _idx_ii, int _idx_jj )
{
//	auto panel   = paneldata[_idx_ii+1][_idx_jj];
//	auto wall  = walldata[_idx_ii][_idx_jj] & ( 1 << 1 );

//	if( panel && !wall ) return true;
	return false;
}
// 左.
bool check_left( int _idx_ii, int _idx_jj )
{
//	auto panel  = paneldata[_idx_ii][_idx_jj-1];
//	auto wall  = walldata[_idx_ii][_idx_jj] & ( 1 << 2 );

//	if( panel && !wall ) return true;
	return false;
}
// 右.
bool check_right( int _idx_ii, int _idx_jj )
{
//	auto panel = paneldata[_idx_ii][_idx_jj+1];
//	auto wall  = walldata[_idx_ii][_idx_jj] & ( 1 << 3 );

//	if( panel && !wall ) return true;
	return false;
}

bool panelcheck( unsigned char _p[][25], int _idx_ii, int _idx_jj )
{
	if( _p[_idx_ii][_idx_jj] ){
		bool isTop, isBtm, isLeft, isRight;
		isTop = isBtm = isLeft = isRight = false;

		if( _idx_ii >  0 ) isTop	= check_top( _idx_ii, _idx_jj );
		if( _idx_ii < 25 ) isBtm	= check_btm( _idx_ii, _idx_jj );
		if( _idx_jj >  0 ) isLeft	= check_left( _idx_ii, _idx_jj );
		if( _idx_jj < 25 ) isRight	= check_right( _idx_ii, _idx_jj );

		if( isTop || isBtm || isLeft || isRight ){
			auto up_left	= _p[_idx_ii-1][_idx_jj-1];	// 左上.
			auto up_right	= _p[_idx_ii-1][_idx_jj+1];	// 右上.
			auto low_left	= _p[_idx_ii+1][_idx_jj-1];	// 左下.
			auto low_right	= _p[_idx_ii+1][_idx_jj+1];	// 右下.

			if( isTop ){
				if( isLeft || isRight ){
					if( isLeft ){ if( !up_left ) return true; }
					else if( isRight ){ if( !up_right ) return true; }
				}
			}
			if( isBtm ){
				if( isLeft || isRight ){
					if( isLeft ){ if( !low_left ) return true; }
					else if( isRight ){ if( !low_right ) return true; }
				}
			}
		}
	}

	return false;
}

#endif // __MAPDATA_H__

