/*
 cmlibpower sample

 Copyright (C) 2011 Team Otwibaco Rights Reserved.
*/

#include <pspkernel.h>
#include <pspctrl.h>
#include <string.h>
#include "cmlibpower.h"		// Thanks for Team Otwibaco

PSP_MODULE_INFO("cmlibpower_sample", 0x1000, 1, 0);

typedef struct
{
	char *moduleName;
	char *modulePath;
} prxCmLibLst;

int running = 0;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  LOAD LIBRARIES
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define NELEMS(a) (sizeof(a) / sizeof(a[0]))
//-------------------------------
int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0) return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}
//-------------------------------
int loadLibraries( void )
{
	int i;
	SceIoStat stat;
	prxCmLibLst libLst[] = {
		{ "cmlibPower", "ms0:/seplugins/lib/cmlibpower.prx" }
	};
	
	while( sceKernelFindModuleByName( "sceKernelLibrary" ) == NULL ) sceKernelDelayThread( 1000 );

	for( i = 0; i < NELEMS(libLst); i++ ){
		// ms0's module checked
		if( sceKernelFindModuleByName(libLst[i].moduleName) == NULL ){
			// ef0's module checked
			if(sceIoGetstat(libLst[i].modulePath, &stat) < 0){
				libLst[i].modulePath[0] = 'e';
				libLst[i].modulePath[1] = 'f';
				
				if(sceIoGetstat(libLst[i].modulePath, &stat) < 0) continue;
			}
			
			LoadStartModule(libLst[i].modulePath);
		}
	}
		
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  main_thread	
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main_thread(SceSize args, void *argp)
{
	// LOAD LIBRARIES
	loadLibraries();
	
	SceCtrlData pad;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	// SET KEYS
	u32 buttonsToSleep    = PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_TRIANGLE;
	u32 buttonsToReboot   = PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_SQUARE;
	u32 buttonsToshutdown = PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_CIRCLE;
	
	while (running)
	{
		sceCtrlPeekBufferPositive(&pad, 1);
		
		// SLEEP MODE
		if( (pad.Buttons& buttonsToSleep) == buttonsToSleep && (buttonsToSleep) ){
			libPowerControll(SLEEP_MODE);
		}

		// REBOOT MODE
		if( (pad.Buttons& buttonsToReboot) == buttonsToReboot && (buttonsToReboot) ){
			libPowerControll(REBOOT_MODE);
		}

		// SHUDOWN MODE
		if( (pad.Buttons& buttonsToshutdown) == buttonsToshutdown && (buttonsToshutdown) ){
			libPowerControll(SHUTDOWN_MODE);
		}
		
		sceKernelDelayThread(50000);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  ENTRY POINT
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int module_start(SceSize args, void *argp)
{
	running = 1;
	SceUID main_thid = sceKernelCreateThread("main", main_thread, 32, 0x800, 0, NULL);
	if(main_thid >= 0)sceKernelStartThread(main_thid, args, argp);

	return 0;
}

int module_stop(SceSize args, void *argp)
{
	running = 0;
	return 0;
}
