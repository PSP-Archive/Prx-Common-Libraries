#include "common.h"

void libmRemoveContext(MenuContext* Context)
{
	if( !Context || !IS_OPT_FUNC_F(Context->opt) ) return;
	
	MenuItem* Curr = Context->Root;
	
	
	//メニュー全アイテムを削除(メモリ解放）
	while( Curr )
	{
		MenuItem *last = Curr;
		
		if ( Curr->Type == MenuContainer && Curr->Children )
		{
			Curr = Curr->Children;
		}
		else
		{
			Curr = Curr->Next;
			
			if (!Curr && last->Parent)
			{
				MenuItem *last2 = last;
				while(last2->Parent->Parent && !last2->Parent->Next)
				{
					MenuItem *parent = last2->Parent;
					Context->opt->func.free_p(last2);
					last2 = parent;
				}
				Curr = last2->Parent->Next;
				Context->opt->func.free_p(last2->Parent);
			}
		}
		
		Context->opt->func.free_p(last);
	}
	
	//コンテキスト削除（メモリ解放）
	Context->opt->func.free_p(Context);
}
