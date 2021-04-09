#include "common.h"

MenuItem* libmGetPrevItem( MenuItem *Item , bool Invalid_Skip )
{
	if( !Item || !Item->Prev ) return NULL;
	
	MenuItem *Ret	= NULL;
	MenuItem *Curr	= Item->Prev;
	
	while(Curr)
	{
		if( !Invalid_Skip || (Invalid_Skip && !libmIsInvalidItem(Curr)) )
		{
			Ret = Curr;
			break;
		}
		
		Curr = Curr->Prev;
	}
	
	return Ret;
}
