	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibCtrlHookKernel",0x00090000,0x00040005
	STUB_FUNC  0x7F2CE163,libCtrlHookGetRawData
	STUB_FUNC  0xE2F8F690,libCtrlHookSetHandler
	STUB_FUNC  0x9390C985,libCtrlHookSetInvalidButtons
	STUB_FUNC  0xD8D2CC33,libCtrlHookDeleteInvalidButtons
	STUB_END
