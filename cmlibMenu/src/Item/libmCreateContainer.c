#include "common.h"

// コンテナ作成
MenuItem* libmCreateContainer(libmOpt *opt , const char* Name )
{
	return _createItem(opt,Name,MenuContainer);
}

