#include "common.h"

MenuItem* libmGetBottomItem( MenuItem *Item , bool Invalid_Skip )
{
	if( !Item || !Item->Next ) return NULL;
	
	MenuItem *Ret	= NULL;
	MenuItem *Curr	= Item;
	
	while(Curr)
	{
		Curr = libmGetNextItem(Curr,Invalid_Skip);
		
		if( Curr ) Ret = Curr;
	}
	
	return Ret;
}
