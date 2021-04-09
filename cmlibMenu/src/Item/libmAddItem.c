#include "common.h"

MenuItem* libmAddItem(MenuContext* Context, MenuItem* Parent, MenuItem* Item,u32 font_color,u32 back_color, int actionID, int Data)
{
	//Context または Item が出来ていなければ何せず抜ける
	if( !Context || !Item ) return NULL;
	
	MenuItem *Target = ( Parent ? Parent->Children : Context->Root );
	
	//値をセット
	Item->actionID		= actionID;
	Item->Data			= Data;
	Item->Parent		= Parent;
	
	Item->Color.Font	= font_color;
	Item->Color.Back	= back_color;
	
	if( Target )
	{
		MenuItem *Curr = Target;
		
		while (Curr->Next)
		{
			Curr = Curr->Next;
		}
		
		//アイテムの前と後を設定
		Curr->Next = Item;
		Item->Prev = Curr;
	}
	else
	{
		//アイテムが一つもない(つまり一番最初)
		
		if( Parent )
		{
			Parent->Children	= Item;
		}
		else
		{
			Context->Root		= Item;
		}
		
		//前後のアイテムはない
		Item->Prev = NULL;
		Item->Next = NULL;
	}
	
	return Item;
}
