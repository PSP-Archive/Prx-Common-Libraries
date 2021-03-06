#include "common.h"

MenuItem* _createItem(libmOpt *opt ,const char* Name,MenuItemType type)
{
	MenuItem* Item = NULL;
	
	
	if( IS_OPT_FUNC_M(opt) )
	{
		Item = (MenuItem*)opt->func.malloc_p(sizeof(MenuItem));
	}
	else if( IS_OPT_LIST(opt) && opt->count < GET_ARRAY_SIZE(opt->list.size) )
	{
		Item = opt->list.val + opt->count;
	}
	
	//Item作成失敗
	if(!Item) return NULL;
	
	opt->count++;
	
	memset(Item,0,sizeof(MenuItem));
	
	//最低限必要な項目を設定
	Item->Visible		= true;
	Item->Disable		= false;
	
	Item->Name			= Name;
	Item->Type			= type;
	
	Item->Color.Font	= LIBM_NO_DRAW;
	Item->Color.Back	= LIBM_NO_DRAW;
	//Item->Color.Line	= LIBM_NO_DRAW;
	
	return Item;
}
