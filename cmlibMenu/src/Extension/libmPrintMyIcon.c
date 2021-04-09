#include "common.h"

void libmPrintMyIcon(int x, int y, u32 fg, u32 bg, const char *icon, u32 size, libm_draw_info *dinfo){
	u32 glyph_x = 0;
	u32 glyph_y = 0;
	u8 bitmap = *icon;
	u8 shift =  0x80;
	u32 color;
	void *put_addr = libmMakeDrawAddr(x, y, dinfo);
	u8 pixel_size = dinfo->vinfo->pixelSize;
	u32 lfsize = dinfo->vinfo->lineSize - (size * pixel_size);
	
	while(glyph_y < size){
		while(glyph_x < size){
			color = bitmap & shift ? fg : bg;
			if(color != 0){
				libmPoint(put_addr, color, dinfo);
			}
			
			glyph_x++;
			put_addr += pixel_size;
			if(shift == 0x1){
				icon++;
				bitmap = *(icon);
				shift = 0x80;
			}
			else{
				shift >>= 1;
			}
		}
		
		glyph_y++;
		put_addr += lfsize;
		glyph_x = 0;
	}
}

