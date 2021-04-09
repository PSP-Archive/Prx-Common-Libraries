	.set noreorder

#include "pspstub.s"

	STUB_START "cmLibLog",0x40090000,0x000F0005
	STUB_FUNC  0x5412BB27,liblogCreateLog
	STUB_FUNC  0xED3F10F9,liblogDestroyLog
	STUB_FUNC  0xB3154015,liblogClear
	STUB_FUNC  0x3DD9A7F7,liblogPrint
	STUB_FUNC  0x16E92A41,liblogPrintf
	STUB_FUNC  0xCED85FF6,liblogPrintBool
	STUB_FUNC  0xCBEC0A7A,liblogPrintInt
	STUB_FUNC  0x2F4B2C08,liblogPrintUint
	STUB_FUNC  0xDD8AFA7E,liblogPrintU64
	STUB_FUNC  0xF7F19077,liblogPrintHex
	STUB_FUNC  0xAE1CB524,liblogPrintHex64
	STUB_FUNC  0x2D9917DB,liblogPrintPspModel
	STUB_FUNC  0x3D5933B3,liblogPrintMaxFreeMem
	STUB_FUNC  0xFC17F31B,liblogSetLogName
	STUB_FUNC  0xEBAE0015,liblogGetLogName
	STUB_END
