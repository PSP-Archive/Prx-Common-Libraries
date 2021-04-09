	.set noreorder

#include "pspimport.s"

// Build files
// cmlibConv_0000.o cmlibConv_0001.o cmlibConv_0002.o cmlibConv_0003.o cmlibConv_0004.o cmlibConv_0005.o cmlibConv_0006.o cmlibConv_0007.o cmlibConv_0008.o cmlibConv_0009.o cmlibConv_0010.o

#ifdef F_cmlibConv_0000
	IMPORT_START "cmlibConv",0x40090000
#endif
#ifdef F_cmlibConv_0001
	IMPORT_FUNC  "cmlibConv",0xA5FB41AF,libConvSjis_Utf16
#endif
#ifdef F_cmlibConv_0002
	IMPORT_FUNC  "cmlibConv",0xD70ACB4D,libConvSjis_to_Utf8
#endif
#ifdef F_cmlibConv_0003
	IMPORT_FUNC  "cmlibConv",0x878BFA6D,libConvSjis_to_Utf16
#endif
#ifdef F_cmlibConv_0004
	IMPORT_FUNC  "cmlibConv",0x44A61D96,libConvUtf16_Sjis
#endif
#ifdef F_cmlibConv_0005
	IMPORT_FUNC  "cmlibConv",0x61ADA695,libConvUtf16_to_Sjis
#endif
#ifdef F_cmlibConv_0006
	IMPORT_FUNC  "cmlibConv",0xCEE051FF,libConvUtf8_Utf16
#endif
#ifdef F_cmlibConv_0007
	IMPORT_FUNC  "cmlibConv",0x87F24889,libConvUtf8_to_Utf16
#endif
#ifdef F_cmlibConv_0008
	IMPORT_FUNC  "cmlibConv",0xFA93721C,libConvUtf16len
#endif
#ifdef F_cmlibConv_0009
	IMPORT_FUNC  "cmlibConv",0xBE752A83,libConvUtf8_to_Sjis
#endif
#ifdef F_cmlibConv_0010
	IMPORT_FUNC  "cmlibConv",0xEC1B9901,libConvFreeMem
#endif
