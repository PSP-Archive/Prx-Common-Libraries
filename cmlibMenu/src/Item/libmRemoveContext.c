#include "common.h"

void libmRemoveContext(MenuContext* Context)
{
	if( !Context || !IS_OPT_FUNC_F(Context->opt) ) return;
	
	MenuItem* Curr = Context->Root;
	
	
	//���j���[�S�A�C�e�����폜(����������j
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
	
	//�R���e�L�X�g�폜�i����������j
	Context->opt->func.free_p(Context);
}
