	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibCtrlHookUser",0x40090000,0x00020005
	STUB_FUNC  0x7F2CE163,libCtrlHookGetRawData
	STUB_FUNC  0xE2F8F690,libCtrlHookSetHandler
	STUB_END
