#include "common.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  InitBuffers
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//#define	VRAM_ADDR_TOP		0x40000000

bool libmInitBuffers_ForHook( int opt, void *topaddr, int bufferwidth, int pixelformat, int sync, libm_draw_info *dinfo )
{
	int mode;
	dinfo->convert	= NULL;
	dinfo->blend	= NULL;

	dinfo->vinfo->buffer	= topaddr;
	dinfo->vinfo->lineWidth	= bufferwidth;
	dinfo->vinfo->format	= pixelformat;

	if( !dinfo->vinfo->buffer || !dinfo->vinfo->lineWidth ) return false;

	sceDisplayGetMode( &mode, &dinfo->vinfo->width, &dinfo->vinfo->height);

//	dinfo->vinfo->buffer= (void*)( (uintptr_t)dinfo->vinfo->buffer | VRAM_ADDR_TOP );
	
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
	return true;
}
