#include "common.h"


bool libmInitBuffers( int opt ,int sync, libm_draw_info *dinfo )
{
	int mode;
	
	dinfo->convert	= NULL;
	dinfo->blend	= NULL;
	
	if( opt & LIBM_FMT_MASK )
	{
		int format;
		
		dinfo->psx = 0;
		dinfo->psy = 0;
		
		switch( opt & LIBM_FMT_MASK )
		{
			case LIBM_DRAW_INIT5650	: format = PSP_DISPLAY_PIXEL_FORMAT_565 ; break;
			case LIBM_DRAW_INIT4444	: format = PSP_DISPLAY_PIXEL_FORMAT_4444; break;
			case LIBM_DRAW_INIT5551	: format = PSP_DISPLAY_PIXEL_FORMAT_5551; break;
			default 				: format = PSP_DISPLAY_PIXEL_FORMAT_8888;
		}
		
		dinfo->vinfo->format	= format;
		dinfo->vinfo->lineWidth	= BUF_WIDTH;
		dinfo->vinfo->buffer	= (void*) (VRAM_ADDR_TOP | (u32) sceGeEdramGetAddr());
		
		sceDisplaySetMode(0, SCR_WIDTH, SCR_HEIGHT);
		sceDisplaySetFrameBuf((void *) dinfo->vinfo->buffer, BUF_WIDTH, dinfo->vinfo->format, sync);
	}
	
	//LIBM_DRAW_INIT‚µ‚Ä‚¢‚½ê‡‚Å‚àAŽÀÛ‚É•ÏX‚³‚ê‚Ä‚¢‚é‚©‚ðÄŽæ“¾
	sceDisplayGetMode( &mode, &dinfo->vinfo->width, &dinfo->vinfo->height);
	sceDisplayGetFrameBuf( &dinfo->vinfo->buffer, &dinfo->vinfo->lineWidth, &dinfo->vinfo->format, sync );
	
	if( !dinfo->vinfo->buffer || !dinfo->vinfo->lineWidth ) return false;
	
	dinfo->vinfo->buffer= (void*)( (uintptr_t)dinfo->vinfo->buffer | VRAM_ADDR_TOP );
	
	dinfo->vinfo->pixelSize	= ( dinfo->vinfo->format == PSP_DISPLAY_PIXEL_FORMAT_8888 ? 4 : 2 );
	dinfo->vinfo->lineSize	= dinfo->vinfo->lineWidth * dinfo->vinfo->pixelSize;
	dinfo->vinfo->frameSize	= dinfo->vinfo->lineSize * dinfo->vinfo->height;
	dinfo->vinfo->opt		= opt;
	
	switch( dinfo->vinfo->format )
	{
		case PSP_DISPLAY_PIXEL_FORMAT_4444:
		{
			dinfo->convert = libmConvert8888_4444;
			if( opt & LIBM_DRAW_BLEND ) dinfo->blend	= libmAlphaBlend4444;
			
			break;
		}
		case PSP_DISPLAY_PIXEL_FORMAT_5551:
		{
			dinfo->convert = libmConvert8888_5551;
			if( opt & LIBM_DRAW_BLEND ) dinfo->blend	= libmAlphaBlend5551;
			
			break;
		}
		case PSP_DISPLAY_PIXEL_FORMAT_565:
		{
			dinfo->convert = libmConvert8888_5650;
			if( opt & LIBM_DRAW_BLEND ) dinfo->blend	= libmAlphaBlend5650;
			
			break;
		}
		
		case PSP_DISPLAY_PIXEL_FORMAT_8888:
		{
			if( opt & LIBM_DRAW_BLEND ) dinfo->blend	= libmAlphaBlend8888;
			
			break;
		}
	}
	
	if( opt & LIBM_FMT_MASK ) libmClearBuffers(dinfo);
	
	return true;
}
