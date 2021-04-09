
#include "common.h"

/*---------------------------------------------------------------------------
  Shift_JISの一文字をUTF-16に変換する
    sjis: Shift_JIS
    return: UTF-16
---------------------------------------------------------------------------*/
u16 libConvSjis_Utf16(u16 sjis)
{
	const u16 *table;

	if(SU == NULL)
	{
		int ret = LoadFile(1);
		if(ret < 0)return ret;
		SetSUPoint();
	}
	if ((table = StoU_convert_table[sjis >> 8]) != ERR)
		return table[sjis & 0xff];

	return 0;
}
