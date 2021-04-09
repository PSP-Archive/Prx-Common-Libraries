#include "common.h"

extern char *font_cg, *font_hankaku_kana, *font_sjis, *font_icon;
extern char *no_font;

inline int libmPrintSymbolXY( int x, int y, u32 color1, u32 color2, u32 color3, u32 color0, const char *str, libm_draw_info *dinfo )
{
	void *put_addr;
	
	const char *glyph;
	u8  chr_width_bytes;
	u16 glyph_line_data;
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
		if( ( (dinfo->vinfo->opt & LIBM_DRAW_RETURN) && x > DRAW_CHR_XMAX  ) )
		{
			y += LIBM_CHAR_HEIGHT;
			x = 0;
		}
		
		if( (dinfo->vinfo->opt & LIBM_DRAW_RETURN) && y > DRAW_CHR_YMAX ) y = 0;
		
		//‘¦À‚ÉŽŸ‚Ì•¶Žš‚Ö
		if( (!(dinfo->vinfo->opt & LIBM_DRAW_RETURN) && (x > DRAW_CHR_XMAX || y > DRAW_CHR_YMAX)) || x < 0 || y < 0 ) continue;
		
		put_addr = libmMakeDrawAddr( x, y, dinfo );
		
		/* ƒOƒŠƒtŽæ“¾ */
		glyph = &(font_icon[(unsigned char)str[i] * LIBM_CHAR_HEIGHT * 2]);
		
		//int fd;
		//fd = sceIoOpen("ms0:/icon_log.bin", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777);
		//sceIoWrite(fd, glyph, 96);
		//sceIoClose(fd);
		
		chr_width_bytes = LIBM_CHAR_WIDTH * dinfo->vinfo->pixelSize;
		
		for( glyph_y = 0; glyph_y < LIBM_CHAR_HEIGHT; glyph_y++, put_addr += dinfo->vinfo->lineSize - chr_width_bytes )
		{
			glyph_line_data = (((u16)glyph[glyph_y * 2]) << 8) | (glyph[(glyph_y * 2) + 1] & 0xFF);
			
			//fd = sceIoOpen("ms0:/line_log.bin", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777);
	        //sceIoWrite(fd, &glyph_line_data, sizeof(glyph_line_data));
	        //sceIoClose(fd);
			
			for( glyph_x = 0; glyph_x < LIBM_CHAR_WIDTH	; glyph_x++, glyph_line_data <<= 2, put_addr += dinfo->vinfo->pixelSize )
			{
				color = (glyph_line_data & 0xC000) >> 14;
				
				//fd = sceIoOpen("ms0:/line_log.bin", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777);
		        //sceIoWrite(fd, &color, sizeof(color));
		        //sceIoClose(fd);
				
				switch(color){
				    case 1:
				        color = color1;
				        break;
			        
			        case 2:
			            color = color2;
			            break;
		            
		            case 3:
		                color = color3;
		                break;
	                
	                default:
	                    color = color0;
                }
				
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
