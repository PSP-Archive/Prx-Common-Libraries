#include "common.h"

MenuItem* libmCreateTriggerButton(libmOpt *opt , const char* Name )
{
	return _createItem(opt,Name,TriggerButton);
}

