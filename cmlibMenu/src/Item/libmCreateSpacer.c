#include "common.h"

MenuItem* libmCreateSpacer(libmOpt *opt , const char* Name )
{
	return _createItem(opt,Name,Spacer);
}

