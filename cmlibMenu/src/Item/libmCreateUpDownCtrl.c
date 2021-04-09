#include "common.h"

MenuItem* libmCreateUpDownCtrl(libmOpt *opt ,const char* Name,float Now,float Step,float Min, float Max,bool type)
{
	MenuItem* Item = _createItem(opt,Name,UpDownCtrl);
	
	//Item�쐬���s
	if(!Item) return NULL;
	
	if(Now >= Min && Now <= Max)
	{
		//���ݒl���ŏ��l�ȏ� & �ő�l�ȓ�
		Item->Ctrl.UD.Now =  Now;
	}
	else
	{
		//���ݒl���ŏ��l�ƍő�l�͈̔͊O
		Item->Ctrl.UD.Now =  Min;
	}
	
	
	Item->Ctrl.UD.Step	= Step;
	Item->Ctrl.UD.Min	= Min;
	Item->Ctrl.UD.Max	= Max;
	
	Item->Ctrl.UD.type	= type;
	
	return Item;
}

