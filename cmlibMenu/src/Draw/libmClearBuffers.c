#include "common.h"

void libmClearBuffers(libm_draw_info *dinfo)
{
	//memset(dinfo->vinfo->buffer ,0, dinfo->vinfo->frameSize );
	void *addr = dinfo->vinfo->buffer;
	void *end_addr = dinfo->vinfo->buffer + dinfo->vinfo->frameSize;
	for(; addr < end_addr; addr += 4){
	    *(u32*)addr = 0;
    }
}

