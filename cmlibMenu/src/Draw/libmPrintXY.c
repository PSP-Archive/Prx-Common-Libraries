#include "common.h"

/*
#include "../fonts/font_cg.c"

#ifdef LNGJPN
#include "../fonts/misaki8x8.c"
#endif
*/

#define	PB_INVALID_FONT			('?' * LIBM_CHAR_HEIGHT)
#define	PB_INVALID_SJIS_INDEX	(0xFFFF)

extern char *font_cg, *font_hankaku_kana, *font_sjis, *font_icon;
extern char *no_font;

inline int libmPrintXY( int x, int y, u32 fg, u32 bg, const char *str, libm_draw_info *dinfo )
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
			y += LIBM_CHAR_HEIGHT;
			x = 0;
		}
		
		if( (dinfo->vinfo->opt & LIBM_DRAW_RETURN) && y > DRAW_CHR_YMAX ) y = 0;
		
		//即座に次の文字へ
		if( (unsigned char)str[i] == '\n' || (!(dinfo->vinfo->opt & LIBM_DRAW_RETURN) && (x > DRAW_CHR_XMAX || y > DRAW_CHR_YMAX)) || x < 0 || y < 0 ) continue;
		
		put_addr = libmMakeDrawAddr( x, y, dinfo );
		
		/* グリフ取得 */
		
//#ifdef LNGJPN
		//日本語サポート
		
		if( (unsigned char)str[i] < 0x80)
		{
			if(font_cg){
    			// 0x80 < アスキー文字
	    		glyph = &(font_cg[(unsigned char)str[i] * LIBM_CHAR_HEIGHT]);
    		}
    		else{
    		    glyph = no_font;
		    }
		}
		else if( (unsigned char)str[i] >= 0xA1 && (unsigned char)str[i] <= 0xDF && font_hankaku_kana)
		{
			if(font_hankaku_kana){
    			//半角カタカナ
	    		glyph = &(font_hankaku_kana[((unsigned char)(str[i] - 0xA1) * LIBM_CHAR_HEIGHT)]);
    		}
    		else{
    		    glyph = no_font;
		    }
		}
		else if( str[i + 1] && font_sjis)
		{
			//（2バイト文字)
			
			u32  glyph_index = PB_INVALID_SJIS_INDEX;
			u8 sjis_hi = str[i] ,sjis_lo = str[i+1];
			
			unsigned char  kuten_hi = sjis_hi - 0x81;
			unsigned short kuten_lo = sjis_lo - 0x40;
			
			//SJIS の無効領域
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
					//美咲フォントの未定義領域
					//return PB_INVALID_SJIS_INDEX;
				}
				else
				{
					/* 16区以降であれば、未定義の9～15区分を引く */
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
				
				//対象文字が格納されているアドレスを求める
				//  = kuten_hi(区) * 1区の文字数(94文字) + kuten_lo * LIBM_CHAR_HEIGHT(文字高 = 8)
				glyph_index =  (kuten_hi * 94 + kuten_lo) * LIBM_CHAR_HEIGHT;
			}
			
			i++;
			
			if( glyph_index != PB_INVALID_SJIS_INDEX )
			{	
				glyph = &(font_sjis[glyph_index]);
			}
			else
			{
				//continue;
				glyph = no_font;
			}
		}
		else
		{
			//該当なし => ?
			//continue;
			glyph = no_font;
		}
/*		
#else
		//英数字のみ
		
		//文字アドレス = 文字コード * 文字高さ（1*8 = 8byte）
		if( (unsigned char)str[i] <= 0x88 )
		{
			glyph = &(font_cg[(unsigned char)str[i] * LIBM_CHAR_HEIGHT]);
		}
		else
		{
			//該当なし => ?
			glyph = no_font;
		}
		
#endif
		*/
		chr_width_bytes = LIBM_CHAR_WIDTH * dinfo->vinfo->pixelSize;
		
		for( glyph_y = 0; glyph_y < LIBM_CHAR_HEIGHT; glyph_y++, put_addr += dinfo->vinfo->lineSize - chr_width_bytes )
		{
			glyph_line_data = glyph[glyph_y];
			
			for( glyph_x = 0; glyph_x < LIBM_CHAR_WIDTH	; glyph_x++, glyph_line_data <<= 1, put_addr += dinfo->vinfo->pixelSize )
			{
				color = glyph_line_data & 0x80 ? fg : bg;
				
				if( color != LIBM_NO_DRAW ) libmPoint( put_addr, color, dinfo );
			}
		}
		
		x += LIBM_CHAR_WIDTH;
	}
	
	if( flag )
	{
		dinfo->psx = x;
		dinfo->psy = y;
	}
	
	return cnt;
}
