#include "common.h"

MenuItem* libmGetTopItem( MenuItem *Item , bool Invalid_Skip )
{
	if( !Item || !Item->Prev ) return NULL;
	
	MenuItem *Ret 	= NULL;
	MenuItem *Curr	= Item;
	
	while( Curr )
	{
		Curr = libmGetPrevItem(Curr,Invalid_Skip);
		
		if( Curr )	Ret  = Curr;
	}
	
	return Ret;
}


