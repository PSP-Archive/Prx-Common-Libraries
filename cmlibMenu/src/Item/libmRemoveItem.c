#include "common.h"

void libmRemoveItem( MenuContext *Context , MenuItem* Item )
{
	if( !Context || !Item || !IS_OPT_FUNC_F(Context->opt) ) return;
	
	if( Item->Type == MenuContainer )
	{
		//削除対象がコンテナーなら、中の子を全て削除（メモリ解放）
		MenuItem* Curr = Item->Children;
		
		while( Curr )
		{
			MeniItem *next = Curr->Next;
			libmRemoveItem(Context, Curr);
			Curr = next;
		}
	}
	
	//削除対象 前と後のアイテムをつなぐ
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
	
	//親の子が削除対象なら NULL に
	if( Item->Parent && Item->Parent->Children == Item ) Item->Parent->Children = NULL;
	
	//メニューのルートが削除対象なら ルート変更
	if( Item == Context->Root ) Context->Root = Item->Next;
	
	//アイテム削除（メモリ解放）
	Context->opt->func.free_p(Item);
};
