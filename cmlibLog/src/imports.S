	.set noreorder

#include "pspimport.s"

	IMPORT_START	"SysMemForKernel", 0x00010011
	IMPORT_FUNC		"SysMemForKernel", 0x6373995D, sceKernelGetModel
