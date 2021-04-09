#include "common.h"

MenuItem* libmCreateUpDownCtrl(libmOpt *opt ,const char* Name,float Now,float Step,float Min, float Max,bool type)
{
	MenuItem* Item = _createItem(opt,Name,UpDownCtrl);
	
	//Item作成失敗
	if(!Item) return NULL;
	
	if(Now >= Min && Now <= Max)
	{
		//現在値が最小値以上 & 最大値以内
		Item->Ctrl.UD.Now =  Now;
	}
	else
	{
		//現在値が最小値と最大値の範囲外
		Item->Ctrl.UD.Now =  Min;
	}
	
	
	Item->Ctrl.UD.Step	= Step;
	Item->Ctrl.UD.Min	= Min;
	Item->Ctrl.UD.Max	= Max;
	
	Item->Ctrl.UD.type	= type;
	
	return Item;
}

