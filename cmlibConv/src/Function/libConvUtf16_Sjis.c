
#include "common.h"

/*---------------------------------------------------------------------------
  UTF-16の一文字をShift_JISに変換する
    utf16: UTF-16
    return: Shift_JIS
---------------------------------------------------------------------------*/
u16 libConvUtf16_Sjis(u16 utf16)
{
    const u16 *table;
	
	if(US == NULL)
	{
		int ret = LoadFile(2);
		if(ret < 0)return ret;
		SetUSPoint();
	}
    if ((table = UtoS_convert_table[utf16 >> 8]) != ERR){
        return table[utf16 & 0xff];
	}

    return 0;
}
