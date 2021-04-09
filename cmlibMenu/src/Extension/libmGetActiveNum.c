#include "common.h"

int libmGetActiveNum(MenuContext *Context, MenuItem *Item , bool Invalid_Skip )
{
	MenuItem *now = libmGetActive(Context);
	MenuItem *top;
	int ret = 0;

	if(Item)top = Item;
	else top = libmGetTopItem( now, Invalid_Skip );

	if(!top)return 0;
	MenuItem *next = top;

	while( next )
	{
		if(next == now)return ret;
		next = libmGetNextItem(next,Invalid_Skip);
		ret ++;
	}
	return -1;
}

