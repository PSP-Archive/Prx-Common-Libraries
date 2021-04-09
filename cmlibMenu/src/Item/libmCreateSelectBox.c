#include "common.h"

MenuItem* libmCreateSelectBox(libmOpt *opt ,const char* Name,const char *List[],int Selected)
{
	MenuItem* Item = _createItem(opt,Name,SelectBox);
	
	//Item作成失敗
	if(!Item) return NULL;
	
	//手抜きで、選択済みアイテムはリストの範囲内かチェックしてない
	Item->Ctrl.SB.Index	= Selected;
	Item->Ctrl.SB.List	= List;
	
	return Item;
}
