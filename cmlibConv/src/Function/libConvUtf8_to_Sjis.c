
#include "common.h"

/*---------------------------------------------------------------------------
  UFT-8Nの文字列をShift_JISに変換する
    *sjis: 変換後の文字列(Shift_JIS)へのポインタ
    *utf8: UFT-8N文字列へのポインタ
---------------------------------------------------------------------------*/
void libConvUtf8_to_Sjis(void *sjis, const char *utf8)
{
	char *buf = mem_alloc(strlen(utf8)*2);
	
	libConvUtf8_to_Utf16((void *)buf, utf8);
	//UTF-8をUTF-16に変換
	libConvUtf16_to_Sjis(sjis, buf);
	//UTF-16をSJISに変換
	
	mem_free(buf);
}
