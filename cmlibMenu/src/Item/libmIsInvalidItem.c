#include "common.h"

//�A�C�e���������ȕ����ǂ���
bool libmIsInvalidItem(MenuItem *Item)
{
	return ( !Item || Item->Type == Spacer || !Item->Visible || Item->Disable);
}

