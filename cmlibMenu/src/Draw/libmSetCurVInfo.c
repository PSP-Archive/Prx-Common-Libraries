#include "common.h"

void libmSetCurVInfo(int format, void *buf, int width, libm_draw_info *dinfo)
{
	dinfo->vinfo->format	= format;
	dinfo->vinfo->buffer	= buf;
	dinfo->vinfo->width		= width;
}
