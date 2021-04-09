#include "common.h"


#define	PB_INVALID_FONT			('?' * LIBM_CHAR_HEIGHT)
#define	PB_INVALID_SJIS_INDEX	(0xFFFF)


int libmLen(const char *str )
{
	u32	i;
	int cnt;
	
	for( i = 0,cnt = 0; str[i]; i++,cnt++ )
	{
		//即座に次の文字へ
		if( (unsigned char)str[i] == '\n') continue;
		
		if( (unsigned char)str[i] < 0x80 )
		{
			// 0x80 < アスキー文字
		}
		else if( (unsigned char)str[i] >= 0xA1 && (unsigned char)str[i] <= 0xDF )
		{
			//半角カタカナ
		}
		else if( str[i + 1] )
		{
			//（2バイト文字)
			i++;
		}
	}
	
	return cnt;
}

