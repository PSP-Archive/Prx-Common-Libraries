#include "common.h"

bool libmSetOpt( MenuContext* Context ,libmOpt *opt )
{
	if( !Context || !IS_OPT(opt) ) return false;
	
	Context->opt	= opt;
	opt->count		= 0;
	
	return true;
}
