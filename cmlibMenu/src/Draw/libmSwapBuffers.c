#include "common.h"

//もうSwapすらしてない・・・

void libmSwapBuffers(libm_draw_info *dinfo)
{
	sceDisplaySetFrameBuf( dinfo->vinfo->buffer , dinfo->vinfo->lineWidth , dinfo->vinfo->format , PSP_DISPLAY_SETBUF_IMMEDIATE );
	sceDisplayWaitVblankStart();
	sceKernelDelayThread( 11500 );
}
