#include "common.h"

MenuItem* libmCreateCheckBox(libmOpt *opt ,const char* Name, bool State)
{
	MenuItem* Item = _createItem(opt,Name,CheckBox);
	
	//Itemì¬Ž¸”s
	if(!Item) return NULL;
	
	Item->Ctrl.CB_Checked = State;
	
	return Item;
}



