#include "common.h"

#define	PB_INVALID_FONT			('?' * LIBM_CHAR_HEIGHT)
#define	PB_INVALID_SJIS_INDEX	(0xFFFF)

extern char *font_cg, *font_hankaku_kana, *font_sjis, *font_icon;
extern char *no_font;

inline int libmPrintXY16( int x, int y, u32 fg, u32 bg, const char *str, libm_draw_info *dinfo )
{
	void *put_addr;
	
	const char *glyph;
	u8  glyph_line_data, chr_width_bytes;
	u16	glyph_x, glyph_y;
	u32	i,color;
	bool flag = false;
	
	int cnt;
	
	if( x == -1 && y == -1 )
	{
		x = dinfo->psx;
		y = dinfo->psy;
		flag = true;
	}
	
	for( i = 0,cnt = 0; str[i]; i++,cnt++ )
	{
		if( ( (dinfo->vinfo->opt & LIBM_DRAW_RETURN) && x > DRAW_CHR_XMAX  ) || (unsigned char)str[i] == '\n' )
		{
			y += LIBM_CHAR_HEIGHT * 2;
			x = 0;
		}
		
		if( (dinfo->vinfo->opt & LIBM_DRAW_RETURN) && y > DRAW_CHR_YMAX ) y = 0;
		
		//�����Ɏ��̕�����
		if( (unsigned char)str[i] == '\n' || (!(dinfo->vinfo->opt & LIBM_DRAW_RETURN) && (x > DRAW_CHR_XMAX || y > DRAW_CHR_YMAX)) || x < 0 || y < 0 ) continue;
		
		put_addr = libmMakeDrawAddr( x, y, dinfo );
		
		/* �O���t�擾 */
		if( (unsigned char)str[i] < 0x80)
		{
			if(font_cg){
    			// 0x80 < �A�X�L�[����
	    		glyph = &(font_cg[(unsigned char)str[i] * LIBM_CHAR_HEIGHT]);
    		}
    		else{
    		    glyph = no_font;
		    }
		}
		else if( (unsigned char)str[i] >= 0xA1 && (unsigned char)str[i] <= 0xDF && font_hankaku_kana)
		{
			if(font_hankaku_kana){
    			//���p�J�^�J�i
	    		glyph = &(font_hankaku_kana[((unsigned char)(str[i] - 0xA1) * LIBM_CHAR_HEIGHT)]);
    		}
    		else{
    		    glyph = no_font;
		    }
		}
		else if( str[i + 1] && font_sjis)
		{
			//�i2�o�C�g����)
			
			u32  glyph_index = PB_INVALID_SJIS_INDEX;
			u8 sjis_hi = str[i] ,sjis_lo = str[i+1];
			
			unsigned char  kuten_hi = sjis_hi - 0x81;
			unsigned short kuten_lo = sjis_lo - 0x40;
			
			//SJIS �̖����̈�
			if ((sjis_hi < 0x81 || sjis_hi > 0xfc || sjis_lo < 0x40 || sjis_lo > 0xfc))
			{
				//return PB_INVALID_SJIS_INDEX;
			}
			else
			{
				if( sjis_hi > 0x9F ) kuten_hi -= 0x40;
				if( sjis_lo > 0x7E ) kuten_lo--;
				
				kuten_hi <<= 1;
				if( kuten_lo > 0x5D ) kuten_hi++;
				
				kuten_lo %= 0x5E;
				
				if((kuten_hi >= 8 && kuten_hi <= 11) || (kuten_hi >= 13 && kuten_hi <= 14) || (kuten_hi >= 83 && kuten_lo > 5) || (kuten_hi > 83))
				{
					//����t�H���g�̖���`�̈�
					//return PB_INVALID_SJIS_INDEX;
				}
				else
				{
					/* 16��ȍ~�ł���΁A����`��9�`15�敪������ */
					if( kuten_hi > 7 && kuten_hi <=12 )
					{
						//9,10,11,12,
						kuten_hi -= 4;
						//kuten_lo--;
					}	
					else if( kuten_hi >= 15 )
					{
						//9,10,11,12,14,15
						kuten_hi -= 6;
						//kuten_lo--;
					}
				}
				
				//�Ώە������i�[����Ă���A�h���X�����߂�
				//  = kuten_hi(��) * 1��̕�����(94����) + kuten_lo * LIBM_CHAR_HEIGHT(������ = 8)
				glyph_index =  (kuten_hi * 94 + kuten_lo) * LIBM_CHAR_HEIGHT;
			}
			
			i++;
			
			if( glyph_index != PB_INVALID_SJIS_INDEX )
			{	
				glyph = &(font_sjis[glyph_index]);
			}
			else
			{
				glyph = no_font;
			}
		}
		else
		{
			glyph = no_font;
		}

		chr_width_bytes = LIBM_CHAR_WIDTH * 2 * dinfo->vinfo->pixelSize;
		
		for( glyph_y = 0; glyph_y < LIBM_CHAR_HEIGHT; glyph_y++ )
		{
			glyph_line_data = glyph[glyph_y];
			
			int j;
			for(j = 0; j < 2; j++){
    			for( glyph_x = 0; glyph_x < LIBM_CHAR_WIDTH; glyph_x++, glyph_line_data <<= 1, put_addr += dinfo->vinfo->pixelSize * 2 )
	    		{
	    			color = glyph_line_data & 0x80 ? fg : bg;
	    			
	    			if( color != LIBM_NO_DRAW ){
	    			    libmPoint( put_addr, color, dinfo );
	    			    libmPoint( put_addr + dinfo->vinfo->pixelSize, color, dinfo );
	    		    }
	    		}
    			put_addr += dinfo->vinfo->lineSize - chr_width_bytes;
    			glyph_line_data = glyph[glyph_y];
			}
		}
		
		x += LIBM_CHAR_WIDTH * 2;
	}
	
	if( flag )
	{
		dinfo->psx = x;
		dinfo->psy = y;
	}
	
	return cnt;
}

