#include "common.h"

inline int libmPrintfXY16( int x, int y, u32 fg, u32 bg, char *buf ,int bufLen , libm_draw_info *dinfo, const char *format, ... )
{
	va_list ap;
	
	va_start( ap, format );
	vsnprintf( buf, bufLen, format, ap );
	va_end( ap );
	
	return libmPrintXY16( x, y, fg, bg,  buf, dinfo);
}
