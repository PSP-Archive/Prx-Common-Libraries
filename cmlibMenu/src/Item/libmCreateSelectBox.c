#include "common.h"

MenuItem* libmCreateSelectBox(libmOpt *opt ,const char* Name,const char *List[],int Selected)
{
	MenuItem* Item = _createItem(opt,Name,SelectBox);
	
	//Item�쐬���s
	if(!Item) return NULL;
	
	//�蔲���ŁA�I���ς݃A�C�e���̓��X�g�͈͓̔����`�F�b�N���ĂȂ�
	Item->Ctrl.SB.Index	= Selected;
	Item->Ctrl.SB.List	= List;
	
	return Item;
}
