#include "common.h"

inline int libmPutCharXY( int x, int y, u32 fg, u32 bg, const char chr, libm_draw_info *dinfo )
{
	const char str[] = { chr, '\0' };
	return libmPrintXY( x, y, fg, bg, str, dinfo );
}
