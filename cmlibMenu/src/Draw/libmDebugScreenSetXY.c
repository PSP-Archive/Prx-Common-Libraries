#include "common.h"

bool libmDebugScreenSetXY( int x ,int y, libm_draw_info *dinfo )
{
	if( x < 0 || x > LIBM_SETX_MAX || y < 0 || y > LIBM_SETY_MAX ) return false;
	
	dinfo->psx = x * LIBM_CHAR_WIDTH;
	dinfo->psy = y * LIBM_CHAR_HEIGHT;
	
	return true;
}
