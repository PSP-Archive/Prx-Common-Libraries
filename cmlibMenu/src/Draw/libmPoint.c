#include "common.h"

//VRAMへColorを描画（コピー）する際、
//memcpyを使うと処理が遅くなる

inline void libmPoint(void *adr, u32 src, libm_draw_info *dinfo)
{
	u32 tmp = src;
	
	if( dinfo->convert ) src = dinfo->convert(src);
	
	if( dinfo->blend )
	{
		src = dinfo->blend((dinfo->vinfo->format == PSP_DISPLAY_PIXEL_FORMAT_4444 ? tmp >> 8 : tmp >> 24 ),src,(dinfo->vinfo->format == PSP_DISPLAY_PIXEL_FORMAT_8888 ? *(u32*)adr : *(u16*)adr));
	}
	
	if( dinfo->vinfo->format == PSP_DISPLAY_PIXEL_FORMAT_8888 )
	{
		*(u32*)adr = src;
	}
	else
	{
		*(u16*)adr = src;
	}
	
	//memcpy(adr,&src,vinfo.pixelSize);
}
