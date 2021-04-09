#include "common.h"

inline void libmFrame( int sx, int sy, int ex, int ey, u32 color, libm_draw_info *dinfo )
{
	if( color == LIBM_NO_DRAW ) return;
	
	libmLine( sx, sy, ex, sy, color, dinfo );
	libmLine( ex, sy, ex, ey, color, dinfo );
	libmLine( ex, ey, sx, ey, color, dinfo );
	libmLine( sx, ey, sx, sy, color, dinfo );
}
