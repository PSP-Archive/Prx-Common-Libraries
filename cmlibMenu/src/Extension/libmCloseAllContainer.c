#include "common.h"

int libmCloseAllContainer(MenuContext* Context)
{
	if(Context->IsOpen == false)return -1;

	while( Context->Active->Parent ){
		Context->Active = Context->Active->Parent;
		Context->Active->Ctrl.CNT.IsOpen = false;
	}
	Context->Params.Action = Menu_Back;

	return 0;
}

