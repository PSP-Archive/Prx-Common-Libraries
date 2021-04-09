#include "common.h"

MenuItem* libmGetNextItem( MenuItem *Item , bool Invalid_Skip )
{
	if( !Item || !Item->Next ) return NULL;
	
	MenuItem *Ret	= NULL;
	MenuItem *Curr	= Item->Next;
	
	while(Curr)
	{
		if( !Invalid_Skip || (Invalid_Skip && !libmIsInvalidItem(Curr)) )
		{
			Ret = Curr;
			break;
		}
		
		Curr = Curr->Next;
	}
	
	return Ret;
}
