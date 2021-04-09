#include "common.h"

bool libmGetCurVInfo(libm_vram_info *info)
{
	if( !info ) return false;
	
	*info = vinfo;
	
	return true;
}
