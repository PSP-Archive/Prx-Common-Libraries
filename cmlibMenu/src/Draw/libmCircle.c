#include "common.h"

inline void libmCircle( int x, int y, u32 radius, u32 color, libm_draw_info *dinfo )
{
	int cx = 0, cy = radius;
	int d = 3 - 2 * radius;
	
	if( color == LIBM_NO_DRAW || ! radius ) return;
	
	/* �J�n�_ */
	libmPoint( libmMakeDrawAddr(x, y + radius, dinfo), color, dinfo ); /* ( 0, R) */
	libmPoint( libmMakeDrawAddr(x, y - radius, dinfo), color, dinfo ); /* ( 0,-R) */
	libmPoint( libmMakeDrawAddr(x + radius, y, dinfo), color, dinfo ); /* ( R, 0) */
	libmPoint( libmMakeDrawAddr(x - radius, y, dinfo), color, dinfo ); /* (-R, 0) */
	
	for( cx = 0; cx <= cy; cx++ )
	{
		if( d >= 0 )
		{
			d += 10 + 4 * cx - 4 * cy--;
		}
		else
		{
			d += 6 + 4 * cx;
		}
		
		libmPoint( libmMakeDrawAddr(x + cy, y + cx, dinfo), color, dinfo ); /*   0-45  �x */
		libmPoint( libmMakeDrawAddr(x + cx, y + cy, dinfo), color, dinfo ); /*  45-90  �x */
		libmPoint( libmMakeDrawAddr(x - cx, y + cy, dinfo), color, dinfo ); /*  90-135 �x */
		libmPoint( libmMakeDrawAddr(x - cy, y + cx, dinfo), color, dinfo ); /* 135-180 �x */
		libmPoint( libmMakeDrawAddr(x - cy, y - cx, dinfo), color, dinfo ); /* 180-225 �x */
		libmPoint( libmMakeDrawAddr(x - cx, y - cy, dinfo), color, dinfo ); /* 225-270 �x */
		libmPoint( libmMakeDrawAddr(x + cx, y - cy, dinfo), color, dinfo ); /* 270-315 �x */
		libmPoint( libmMakeDrawAddr(x + cy, y - cx, dinfo), color, dinfo ); /* 315-360 �x */
	}
}
