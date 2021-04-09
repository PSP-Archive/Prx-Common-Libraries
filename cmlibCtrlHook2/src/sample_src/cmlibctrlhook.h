#ifndef __CMLIBCTRLHOOK_H__
#define __CMLIBCTRLHOOK_H__

#ifdef __cplusplus
extern "C" {
#endif

// header
#include <pspkernel.h>
#include <pspctrl.h>

// typedef
typedef int (*CTRL_HOOK_HANDLER)(SceCtrlData *pad_data);

// function

/*
	Raw pad_data is acquired.

	@param pad_data - Pointer to a ::SceCtrlData structure used hold the returned pad data.

	@Example

	SceCtrlData pad_data;
	libCtrlHookGetRawData(&pad_data);

*/
int libCtrlHookGetRawData(SceCtrlData *pad_data);

/*
	Sets a function to be called just after sceCtrlCommonFunc of a function is gonna be called.

	@param new_handler - The function.
	@returns - The previous set function (NULL if none);

	@Example:

	CTRL_HOOK_HANDLER previous = NULL;

	int CtrlControl(SceCtrlData *pad_data);

	void somepointofmycode(void)
	{
		previous = libCtrlHookSetHandler(CtrlControl);
	}

	int CtrlControl(SceCtrlData *pad_data)
	{
		// Invalid Circle
		pad_data->Buttons &= ~PSP_CTRL_CIRCLE;

		return previous ? previous(pad_data) : 0;
	}

*/
CTRL_HOOK_HANDLER libCtrlHookSetHandler(CTRL_HOOK_HANDLER new_handler);

#ifdef __cplusplus
}
#endif

#endif

