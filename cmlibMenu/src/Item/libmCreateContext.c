#include "common.h"

#define	WHITE					0xffFFFFFF
#define	GREEN					0xff00FF00
#define	BLACK					0xff000000

#define	GRAY					0xff808080

// Root用の領域確保
MenuContext* libmCreateContext(libmOpt *opt)
{
	MenuContext *context = NULL;
	
	if( !IS_OPT_FUNC_M(opt) ) return NULL;
	
	context = (MenuContext*)opt->func.malloc_p(sizeof(MenuContext));
	
	//Context作成失敗
	if( !context ) return NULL;
	
	memset(context ,0,sizeof(MenuContext));
	
	//初期化（デフォルト値 設定）
	context->HotKey.Show			= PSP_CTRL_NOTE ;
	context->HotKey.Back			= PSP_CTRL_CIRCLE;
	context->HotKey.Select			= PSP_CTRL_CROSS;
	context->HotKey.Up				= PSP_CTRL_UP;
	context->HotKey.Down			= PSP_CTRL_DOWN;
	context->HotKey.Left			= PSP_CTRL_LEFT;
	context->HotKey.Right			= PSP_CTRL_RIGHT;
	
	
	context->MenuInfo.Type			= false;
	
	context->MenuInfo.AutoReturn	= true;
	
	context->Color.Active_Font		= GREEN;
	context->Color.Normal_Font		= WHITE;
	
	context->Color.Active_Back		= BLACK;
	context->Color.Normal_Back		= LIBM_NO_DRAW;
	
	context->Color.Disable_Font		= GRAY;
	context->Color.Disable_Back		= LIBM_NO_DRAW;
	
	context->MenuInfo.Lines		 	= 1;
	
	return context;
}