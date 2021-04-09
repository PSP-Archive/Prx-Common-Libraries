	.set noreorder

#include "pspimport.s"

#カーネルモードのプラグインで
#未定義となる関数を事前にライブラリ側で補う

IMPORT_START	"sceGe_user",0x40010000
IMPORT_FUNC	"sceGe_user",0xE47E40E4,sceGeEdramGetAddr
