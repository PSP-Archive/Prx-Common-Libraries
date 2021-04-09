#include "common.h"

inline int libmPutCharXY16( int x, int y, u32 fg, u32 bg, const char chr, libm_draw_info *dinfo )
{
	const char str[] = { chr, '\0' };
	return libmPrintXY16( x, y, fg, bg, str, dinfo );
}

