	.set noreorder

#include "pspstub.s"


	STUB_START "sceSysreg_driver",0x40090000,0x00020005
	STUB_FUNC  0x8E2FB536,sceSysregAudioIoDisable
	STUB_FUNC  0xBB26CF1F,sceSysregAudioIoEnable
	STUB_END

