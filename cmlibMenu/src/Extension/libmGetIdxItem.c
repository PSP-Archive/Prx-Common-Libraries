#include "common.h"

MenuItem* libmGetIdxItem( MenuItem *Item , bool Invalid_Skip , int Point_Idx )
{
	if( !Item || !Item->Next ) return NULL;
	
	MenuItem *Ret 	= NULL;
	MenuItem *Curr	= Item;
	
	int cnt;
	
	for (cnt = 0; cnt < Point_Idx; cnt++ ){
		Curr = libmGetNextItem(Curr, Invalid_Skip);
	}
	
	if( Curr ){
		Ret = Curr;
	}
	
	return Ret;
}

