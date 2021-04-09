#include "common.h"

//ƒAƒCƒeƒ€‚ª–³Œø‚È•¨‚©‚Ç‚¤‚©
bool libmIsInvalidItem(MenuItem *Item)
{
	return ( !Item || Item->Type == Spacer || !Item->Visible || Item->Disable);
}

