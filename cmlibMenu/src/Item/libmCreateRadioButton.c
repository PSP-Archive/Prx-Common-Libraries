#include "common.h"

MenuItem* libmCreateRadioButton(libmOpt *opt , const char* Name, bool State ,MenuItem *Group )
{
	//親がコンテナーじゃなければ追加出来ない
	
	MenuItem* Item = _createItem(opt,Name,RadioButton);
	
	//Item作成失敗
	if( !Item || !Group || Group->Type != RadioButtonGroup ) return NULL;
	
	//チェック状態
	Item->Ctrl.RB_Group = Group;
	
	//選択済みを現在のアイテムへ
	if( State ) Group->Ctrl.Group_Sel = Item;
	
	return Item;
}


