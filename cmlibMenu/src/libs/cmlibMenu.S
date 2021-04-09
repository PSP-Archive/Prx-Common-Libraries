	.set noreorder

#include "pspimport.s"

// Build files
// cmlibMenu_0000.o cmlibMenu_0001.o cmlibMenu_0002.o cmlibMenu_0003.o cmlibMenu_0004.o cmlibMenu_0005.o cmlibMenu_0006.o cmlibMenu_0007.o cmlibMenu_0008.o cmlibMenu_0009.o cmlibMenu_0010.o cmlibMenu_0011.o cmlibMenu_0012.o cmlibMenu_0013.o cmlibMenu_0014.o cmlibMenu_0015.o cmlibMenu_0016.o cmlibMenu_0017.o cmlibMenu_0018.o cmlibMenu_0019.o cmlibMenu_0020.o cmlibMenu_0021.o cmlibMenu_0022.o cmlibMenu_0023.o cmlibMenu_0024.o cmlibMenu_0025.o cmlibMenu_0026.o cmlibMenu_0027.o cmlibMenu_0028.o cmlibMenu_0029.o cmlibMenu_0030.o cmlibMenu_0031.o cmlibMenu_0032.o cmlibMenu_0033.o cmlibMenu_0034.o cmlibMenu_0035.o cmlibMenu_0036.o cmlibMenu_0037.o cmlibMenu_0038.o cmlibMenu_0039.o cmlibMenu_0040.o cmlibMenu_0041.o cmlibMenu_0042.o cmlibMenu_0043.o cmlibMenu_0044.o cmlibMenu_0045.o cmlibMenu_0046.o cmlibMenu_0047.o cmlibMenu_0048.o cmlibMenu_0049.o cmlibMenu_0050.o cmlibMenu_0051.o cmlibMenu_0052.o cmlibMenu_0053.o cmlibMenu_0054.o cmlibMenu_0055.o cmlibMenu_0056.o cmlibMenu_0057.o cmlibMenu_0058.o cmlibMenu_0059.o cmlibMenu_0060.o 

#ifdef F_cmlibMenu_0000
	IMPORT_START "cmlibMenu",0x40090000
#endif
#ifdef F_cmlibMenu_0001
	IMPORT_FUNC  "cmlibMenu",0x177A922B,libmIsInvalidItem
#endif
#ifdef F_cmlibMenu_0002
	IMPORT_FUNC  "cmlibMenu",0xC076E2D7,libmGetPrevItem
#endif
#ifdef F_cmlibMenu_0003
	IMPORT_FUNC  "cmlibMenu",0x30C9C4D9,libmGetNextItem
#endif
#ifdef F_cmlibMenu_0004
	IMPORT_FUNC  "cmlibMenu",0x25135809,libmGetBottomItem
#endif
#ifdef F_cmlibMenu_0005
	IMPORT_FUNC  "cmlibMenu",0x708A8103,libmGetTopItem
#endif
#ifdef F_cmlibMenu_0006
	IMPORT_FUNC  "cmlibMenu",0x2E7B155E,libmSetOpt
#endif
#ifdef F_cmlibMenu_0007
	IMPORT_FUNC  "cmlibMenu",0x7D4E082B,libmCreateContext
#endif
#ifdef F_cmlibMenu_0008
	IMPORT_FUNC  "cmlibMenu",0xD330D49D,libmRemoveContext
#endif
#ifdef F_cmlibMenu_0009
	IMPORT_FUNC  "cmlibMenu",0x30557939,libmAddItem
#endif
#ifdef F_cmlibMenu_0010
	IMPORT_FUNC  "cmlibMenu",0x84B9B7F2,libmRemoveItem
#endif
#ifdef F_cmlibMenu_0011
	IMPORT_FUNC  "cmlibMenu",0x5DAC8CDD,libmGetHandle
#endif
#ifdef F_cmlibMenu_0012
	IMPORT_FUNC  "cmlibMenu",0x0C001B27,libmRender
#endif
#ifdef F_cmlibMenu_0013
	IMPORT_FUNC  "cmlibMenu",0x90794A8C,libmCreateContainer
#endif
#ifdef F_cmlibMenu_0014
	IMPORT_FUNC  "cmlibMenu",0xBDA0B780,libmCreateRadioButton
#endif
#ifdef F_cmlibMenu_0015
	IMPORT_FUNC  "cmlibMenu",0x407DA9DD,libmCreateRadioButtonGroup
#endif
#ifdef F_cmlibMenu_0016
	IMPORT_FUNC  "cmlibMenu",0x1A302F9C,libmCreateCheckBox
#endif
#ifdef F_cmlibMenu_0017
	IMPORT_FUNC  "cmlibMenu",0x8A40E06C,libmCreateSelectBox
#endif
#ifdef F_cmlibMenu_0018
	IMPORT_FUNC  "cmlibMenu",0xA9123A4A,libmCreateUpDownCtrl
#endif
#ifdef F_cmlibMenu_0019
	IMPORT_FUNC  "cmlibMenu",0x0D60E65C,libmCreateSpacer
#endif
#ifdef F_cmlibMenu_0020
	IMPORT_FUNC  "cmlibMenu",0xD83A6CDC,libmCreateTriggerButton
#endif
#ifdef F_cmlibMenu_0021
	IMPORT_FUNC  "cmlibMenu",0x7AD3AB39,libmInitBuffers
#endif
#ifdef F_cmlibMenu_0022
	IMPORT_FUNC  "cmlibMenu",0x48DD363B,libmSwapBuffers
#endif
#ifdef F_cmlibMenu_0023
	IMPORT_FUNC  "cmlibMenu",0x51954257,libmClearBuffers
#endif
#ifdef F_cmlibMenu_0024
	IMPORT_FUNC  "cmlibMenu",0xE78FBB5D,libmPrintXY
#endif
#ifdef F_cmlibMenu_0025
	IMPORT_FUNC  "cmlibMenu",0x869F8479,libmPrintfXY
#endif
#ifdef F_cmlibMenu_0026
	IMPORT_FUNC  "cmlibMenu",0xB70DD7B4,libmPutCharXY
#endif
#ifdef F_cmlibMenu_0027
	IMPORT_FUNC  "cmlibMenu",0xE2D832BE,libmDebugScreenSetXY
#endif
#ifdef F_cmlibMenu_0028
	IMPORT_FUNC  "cmlibMenu",0xAFADF9A2,libmLine
#endif
#ifdef F_cmlibMenu_0029
	IMPORT_FUNC  "cmlibMenu",0xFC07A4CA,libmPoint
#endif
#ifdef F_cmlibMenu_0030
	IMPORT_FUNC  "cmlibMenu",0xA17FA8DB,libmPointEx
#endif
#ifdef F_cmlibMenu_0031
	IMPORT_FUNC  "cmlibMenu",0x6F97BC8F,libmFillRect
#endif
#ifdef F_cmlibMenu_0032
	IMPORT_FUNC  "cmlibMenu",0x126AABE0,libmCircle
#endif
#ifdef F_cmlibMenu_0033
	IMPORT_FUNC  "cmlibMenu",0x76352024,libmFrame
#endif
#ifdef F_cmlibMenu_0034
	IMPORT_FUNC  "cmlibMenu",0x8D230A74,libmMakeDrawAddr
#endif
#ifdef F_cmlibMenu_0035
	IMPORT_FUNC  "cmlibMenu",0xD51C5C0B,libmConvert8888_5650
#endif
#ifdef F_cmlibMenu_0036
	IMPORT_FUNC  "cmlibMenu",0xD0AC92B6,libmConvert8888_5551
#endif
#ifdef F_cmlibMenu_0037
	IMPORT_FUNC  "cmlibMenu",0x1A3EE88D,libmConvert8888_4444
#endif
#ifdef F_cmlibMenu_0038
	IMPORT_FUNC  "cmlibMenu",0xDB3E9619,libmConvert4444_8888
#endif
#ifdef F_cmlibMenu_0039
	IMPORT_FUNC  "cmlibMenu",0x7786D300,libmConvert5551_8888
#endif
#ifdef F_cmlibMenu_0040
	IMPORT_FUNC  "cmlibMenu",0x9F659346,libmConvert5650_8888
#endif
#ifdef F_cmlibMenu_0041
	IMPORT_FUNC  "cmlibMenu",0x989DD903,libmAlphaBlend8888
#endif
#ifdef F_cmlibMenu_0042
	IMPORT_FUNC  "cmlibMenu",0xF40B821C,libmAlphaBlend4444
#endif
#ifdef F_cmlibMenu_0043
	IMPORT_FUNC  "cmlibMenu",0x78F43955,libmAlphaBlend5551
#endif
#ifdef F_cmlibMenu_0044
	IMPORT_FUNC  "cmlibMenu",0x12757696,libmAlphaBlend5650
#endif
#ifdef F_cmlibMenu_0045
	IMPORT_FUNC  "cmlibMenu",0xFA91BCBF,libmGetColor
#endif
#ifdef F_cmlibMenu_0046
	IMPORT_FUNC  "cmlibMenu",0xCE0C4B66,libmSetCurVInfo
#endif
#ifdef F_cmlibMenu_0047
	IMPORT_FUNC  "cmlibMenu",0x483DAE95,libmLoadFont
#endif
#ifdef F_cmlibMenu_0048
	IMPORT_FUNC  "cmlibMenu",0xB30F8027,libmLen
#endif
#ifdef F_cmlibMenu_0049
	IMPORT_FUNC  "cmlibMenu",0xD96421D1,libmPrintXY16
#endif
#ifdef F_cmlibMenu_0050
	IMPORT_FUNC  "cmlibMenu",0x8700B40A,libmPrintfXY16
#endif
#ifdef F_cmlibMenu_0051
	IMPORT_FUNC  "cmlibMenu",0x0C545004,libmGetIdxItem
#endif
#ifdef F_cmlibMenu_0052
	IMPORT_FUNC  "cmlibMenu",0x698B739C,libmPrintSymbolXY
#endif
#ifdef F_cmlibMenu_0053
	IMPORT_FUNC  "cmlibMenu",0x11CC532D,libmPrintSymbolXY16
#endif
#ifdef F_cmlibMenu_0054
	IMPORT_FUNC  "cmlibMenu",0xEFE94F84,libmCloseAllContainer
#endif
#ifdef F_cmlibMenu_0055
	IMPORT_FUNC  "cmlibMenu",0xBEE39035,libmGetActiveNum
#endif
#ifdef F_cmlibMenu_0056
	IMPORT_FUNC  "cmlibMenu",0x5C018929,libmHookDisplayHandler
#endif
#ifdef F_cmlibMenu_0057
	IMPORT_FUNC  "cmlibMenu",0x37235C97,libmInitBuffers_ForHook
#endif
#ifdef F_cmlibMenu_0058
	IMPORT_FUNC  "cmlibMenu",0x302DCA1A,libmGetFontAddr
#endif
#ifdef F_cmlibMenu_0059
	IMPORT_FUNC  "cmlibMenu",0x83CE3BAE,libmPutCharXY16
#endif
#ifdef F_cmlibMenu_0060
	IMPORT_FUNC  "cmlibMenu",0x12B2120E,libmPrintMyIcon
#endif
