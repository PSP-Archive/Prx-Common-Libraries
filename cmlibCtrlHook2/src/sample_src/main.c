// cmlibCtrlHook_sample(KernelModule)

// header
#include <pspkernel.h>
#include <pspctrl.h>
#include "cmlibctrlhook.h"

// info
PSP_MODULE_INFO("cmlibCtrlHook_sample", PSP_MODULE_KERNEL, 0, 1);

// trigger
#define TRIGGER_KEYS	(PSP_CTRL_LTRIGGER | PSP_CTRL_SQUARE)

// mask
#define MASK_KEYS	(PSP_CTRL_UP | PSP_CTRL_DOWN | PSP_CTRL_LEFT | PSP_CTRL_RIGHT |\
					PSP_CTRL_CIRCLE | PSP_CTRL_CROSS | PSP_CTRL_TRIANGLE | PSP_CTRL_SQUARE |\
					PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_START | PSP_CTRL_SELECT)

// global
int invalid_flag;
CTRL_HOOK_HANDLER previous;

// function
void WaitButtons(u32 buttons)
{
	SceCtrlData pad_data;
	pad_data.Buttons = buttons;

	while((pad_data.Buttons & buttons) != 0)
	{
		libCtrlHookGetRawData(&pad_data);
		sceKernelDelayThread(1000);
	}

	return;
}

int CtrlHandler(SceCtrlData *pad_data)
{
	if(invalid_flag)
	{
		pad_data->Buttons &= ~MASK_KEYS;
	}

	return previous ? previous(pad_data) : 0;
}

int MainThread(SceSize args, void *argp)
{
	SceCtrlData pad_data;

	// set handler
	previous = libCtrlHookSetHandler(CtrlHandler);

	// loop
	while(1)
	{
		// get raw_pad_data
		libCtrlHookGetRawData(&pad_data);

		// on / off invalid_flag
		if((pad_data.Buttons & TRIGGER_KEYS) == TRIGGER_KEYS)
		{
			WaitButtons(TRIGGER_KEYS);
			invalid_flag ^= 1;
		}

		// delay
		sceKernelDelayThread(5000);
	}

	return 0;
}

int module_start(SceSize args, void *argp)
{
	SceUID thid = sceKernelCreateThread("MainThread", MainThread, 16, 0x1000, 0, NULL);

	if(thid > 0)
		sceKernelStartThread(thid, args, argp);

	return 0;
}

int module_stop(SceSize args, void *argp)
{
	return 0;
}

