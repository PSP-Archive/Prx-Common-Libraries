#include "common.h"

void libmRemoveItem( MenuContext *Context , MenuItem* Item )
{
	if( !Context || !Item || !IS_OPT_FUNC_F(Context->opt) ) return;
	
	if( Item->Type == MenuContainer )
	{
		//�폜�Ώۂ��R���e�i�[�Ȃ�A���̎q��S�č폜�i����������j
		MenuItem* Curr = Item->Children;
		
		while( Curr )
		{
			MeniItem *next = Curr->Next;
			libmRemoveItem(Context, Curr);
			Curr = next;
		}
	}
	
	//�폜�Ώ� �O�ƌ�̃A�C�e�����Ȃ�
	if( Item->Prev )
	{
		Item->Prev->Next = Item->Next;
		
		if( Item->Next )
		{
			Item->Next->Prev = Item->Prev;
		}
		else
		{
			Item->Prev->Next = NULL;
		}
	}
	else
	{
		Item->Prev = NULL;
	}
	
	//�e�̎q���폜�ΏۂȂ� NULL ��
	if( Item->Parent && Item->Parent->Children == Item ) Item->Parent->Children = NULL;
	
	//���j���[�̃��[�g���폜�ΏۂȂ� ���[�g�ύX
	if( Item == Context->Root ) Context->Root = Item->Next;
	
	//�A�C�e���폜�i����������j
	Context->opt->func.free_p(Item);
};
