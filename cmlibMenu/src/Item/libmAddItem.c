#include "common.h"

MenuItem* libmAddItem(MenuContext* Context, MenuItem* Parent, MenuItem* Item,u32 font_color,u32 back_color, int actionID, int Data)
{
	//Context �܂��� Item ���o���Ă��Ȃ���Ή�����������
	if( !Context || !Item ) return NULL;
	
	MenuItem *Target = ( Parent ? Parent->Children : Context->Root );
	
	//�l���Z�b�g
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
		
		//�A�C�e���̑O�ƌ��ݒ�
		Curr->Next = Item;
		Item->Prev = Curr;
	}
	else
	{
		//�A�C�e��������Ȃ�(�܂��ԍŏ�)
		
		if( Parent )
		{
			Parent->Children	= Item;
		}
		else
		{
			Context->Root		= Item;
		}
		
		//�O��̃A�C�e���͂Ȃ�
		Item->Prev = NULL;
		Item->Next = NULL;
	}
	
	return Item;
}
