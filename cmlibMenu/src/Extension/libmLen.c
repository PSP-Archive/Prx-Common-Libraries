#include "common.h"


#define	PB_INVALID_FONT			('?' * LIBM_CHAR_HEIGHT)
#define	PB_INVALID_SJIS_INDEX	(0xFFFF)


int libmLen(const char *str )
{
	u32	i;
	int cnt;
	
	for( i = 0,cnt = 0; str[i]; i++,cnt++ )
	{
		//�����Ɏ��̕�����
		if( (unsigned char)str[i] == '\n') continue;
		
		if( (unsigned char)str[i] < 0x80 )
		{
			// 0x80 < �A�X�L�[����
		}
		else if( (unsigned char)str[i] >= 0xA1 && (unsigned char)str[i] <= 0xDF )
		{
			//���p�J�^�J�i
		}
		else if( str[i + 1] )
		{
			//�i2�o�C�g����)
			i++;
		}
	}
	
	return cnt;
}

