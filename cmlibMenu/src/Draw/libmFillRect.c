#include "common.h"

inline void libmFillRect( int sx, int sy, int ex, int ey, u32 color, libm_draw_info *dinfo )
{
	int x, y;
	
	if( color == LIBM_NO_DRAW ) return;
	
	if( sx > ex ) SWAP( &sx, &ex );
	if( sy > ey ) SWAP( &sy, &ey );
	
	for(y = (sy * dinfo->vinfo->lineSize); y < (ey * dinfo->vinfo->lineSize); y += dinfo->vinfo->lineSize){
        for(x = (sx * dinfo->vinfo->pixelSize); x < (ex * dinfo->vinfo->pixelSize); x += dinfo->vinfo->pixelSize){
            libmPoint(dinfo->vinfo->buffer + x + y, color, dinfo );
        }
    }
}

