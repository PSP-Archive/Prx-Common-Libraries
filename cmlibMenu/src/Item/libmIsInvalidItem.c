#include "common.h"

//アイテムが無効な物かどうか
bool libmIsInvalidItem(MenuItem *Item)
{
	return ( !Item || Item->Type == Spacer || !Item->Visible || Item->Disable);
}

