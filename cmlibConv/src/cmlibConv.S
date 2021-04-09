	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibConv",0x40090000,0x000A0005
	STUB_FUNC  0xA5FB41AF,libConvSjis_Utf16
	STUB_FUNC  0xD70ACB4D,libConvSjis_to_Utf8
	STUB_FUNC  0x878BFA6D,libConvSjis_to_Utf16
	STUB_FUNC  0x44A61D96,libConvUtf16_Sjis
	STUB_FUNC  0x61ADA695,libConvUtf16_to_Sjis
	STUB_FUNC  0xCEE051FF,libConvUtf8_Utf16
	STUB_FUNC  0x87F24889,libConvUtf8_to_Utf16
	STUB_FUNC  0xFA93721C,libConvUtf16len
	STUB_FUNC  0xBE752A83,libConvUtf8_to_Sjis
	STUB_FUNC  0xEC1B9901,libConvFreeMem
	STUB_END
