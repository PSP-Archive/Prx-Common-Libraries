// cmlibCtrlHook v2.1 by plum

// header
#include "cmlibctrlhook.h"
#include <systemctrl.h>
#include <string.h>

// info
PSP_MODULE_INFO("cmlibCtrlHook", PSP_MODULE_KERNEL, 2, 1);
PSP_NO_CREATE_MAIN_THREAD();

// define
#define K_EXTRACT_CALL(x) (((((u32)_lw((u32)x)) & ~0x0C000000) << 2) | 0x80000000)
#define MAKE_STUB(a, f) _sw(0x08000000 | (((u32)(f) & 0x0FFFFFFC) >> 2), a); _sw(0, a + 4);

// prototype
int sceCtrlCommonFunc(SceCtrlData *pad_data, int count, int arg2, int func_number);
int sceCtrlCommonOldFunc(SceCtrlData *pad_data, int count, int arg2, int func_number);
void sceCtrlCommonFuncPatched(SceCtrlData *pad_data, int count, int arg2, int func_number);
void sceCtrlCommonFuncOldPatched(SceCtrlData *pad_data, int count, int arg2, int func_number);

// function_ptr
int (*_sceCtrlCommonFunc)(SceCtrlData *pad_data, int count, int arg2, int func_number);

// global
u32 ctrl_jump_addr;
CTRL_HOOK_HANDLER global_handler;

// function
void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

int libCtrlHookGetRawData(SceCtrlData *pad_data)
{
	return _sceCtrlCommonFunc(pad_data, 1, 0, 0);
}

CTRL_HOOK_HANDLER libCtrlHookSetHandler(CTRL_HOOK_HANDLER new_handler)
{
	CTRL_HOOK_HANDLER handler;

	handler = global_handler;
	global_handler = (void *)(((u32)new_handler) | 0x80000000);

	return handler;
}

int sceCtrlCommonFuncControl(SceCtrlData *pad_data, int result)
{
	if(global_handler)
	{
		global_handler(pad_data);
	}

	return result;
}

void HookControllerService(void)
{
	int devkit;
	u32 orgaddr, func_addr;

	// get version
	devkit = sceKernelDevkitVersion();

	// sceCtrlReadBufferPositive
	orgaddr = sctrlHENFindFunction("sceController_Service", "sceCtrl", 0x1F803938);

	if(devkit > 0x06000000)
	{
		// get sceCtrlCommonFunc_addr(6.XX)
		func_addr = K_EXTRACT_CALL(orgaddr + 0xC);
	}
	else
	{
		// get sceCtrlCommonFunc_addr(old)
		func_addr = K_EXTRACT_CALL(orgaddr + 0x8);
	}

	// patch sceCtrlCommonFunc
	if(_lw(func_addr + 0xC) != 0)
	{
		// get sceCtrlCommonFunc_jump_addr
		ctrl_jump_addr = func_addr + 0x10;

		if(devkit > 0x06000000)
		{
			// get func
			_sceCtrlCommonFunc = (void *)sceCtrlCommonFunc;

			// patch
			MAKE_STUB(ctrl_jump_addr - 0x8, sceCtrlCommonFuncPatched);
		}
		else
		{
			// get func
			_sceCtrlCommonFunc = (void *)sceCtrlCommonOldFunc;

			// patch
			MAKE_STUB(ctrl_jump_addr - 0x8, sceCtrlCommonFuncOldPatched);
		}

		// clear
		ClearCaches();
	}

	return;
}

int module_start(SceSize args, void *argp)
{
	// patch
	HookControllerService();
	return 0;
}

int module_stop(SceSize args, void *argp)
{
	return 0;
}

