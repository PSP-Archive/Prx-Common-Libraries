// cmlibCtrlHook_sample(UserModule)

// header
#include <pspkernel.h>
#include <pspctrl.h>
#include "cmlibctrlhook.h"

// info
PSP_MODULE_INFO("cmlibCtrlHook_sample2", PSP_MODULE_USER, 0, 1);

// global
int swap_flag;
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
	if(swap_flag)
	{
		// swap Left / L_trigger & Right / R_trigger buttons
		if(pad_data->Buttons & PSP_CTRL_LTRIGGER)
		{
			pad_data->Buttons |= PSP_CTRL_LEFT;
			pad_data->Buttons &= ~PSP_CTRL_LTRIGGER;
		}
		else if(pad_data->Buttons & PSP_CTRL_RTRIGGER)
		{
			pad_data->Buttons |= PSP_CTRL_RIGHT;
			pad_data->Buttons &= ~PSP_CTRL_RTRIGGER;
		}
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

		// set
		if(pad_data.Buttons & PSP_CTRL_TRIANGLE)
		{
			WaitButtons(PSP_CTRL_TRIANGLE);
			swap_flag ^= 1;
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

