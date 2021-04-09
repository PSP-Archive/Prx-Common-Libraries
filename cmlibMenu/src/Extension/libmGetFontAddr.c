#include "common.h"

extern char *font_cg, *font_hankaku_kana, *font_sjis, *font_icon;

char* libmGetFontAddr(int flag){
	char *ret;
	
	switch(flag){
		case LIBM_FONT_CG:
			ret = font_cg;
			break;
		
		case LIBM_FONT_HANKAKU_KANA:
			ret = font_hankaku_kana;
			break;
		
		case LIBM_FONT_SJIS:
			ret = font_sjis;
			break;
		
		case LIBM_FONT_ICON:
			ret = font_icon;
			break;
		
		default:
			ret = NULL;
	}
	
	return ret;
}

