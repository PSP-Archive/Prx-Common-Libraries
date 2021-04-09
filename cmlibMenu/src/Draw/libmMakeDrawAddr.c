#include "common.h"

inline void* libmMakeDrawAddr( int x, int y, libm_draw_info *dinfo )
{
	return (void*)( dinfo->vinfo->buffer + (( x + y * dinfo->vinfo->lineWidth ) * dinfo->vinfo->pixelSize) );
}
