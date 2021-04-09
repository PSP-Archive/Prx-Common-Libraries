/*
 * Prx Common Libraries - cmlibUpdater
 * main.c
 * 2011/11/01
 * Created by Y.K
 *
 * Thanks to popsdeco and neur0n.
 * Thanks to team Otwibaco developers.
 */

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "net.h"
#include "http.h"
#include "file.h"
#include "script.h"
#include "main.h"

#include "debuglog.h"


PSP_MODULE_INFO( MODULE_NAME, 0, MAJOR_VER, MAINOR_VER );
PSP_MAIN_THREAD_ATTR( PSP_THREAD_ATTR_USER );


int g_disp_flip;
int g_running = 1;


int exit_eboot( void )
{
	g_running = 0;

	if( net_is_connected() == 1 ) {
		net_disconnect_to_apctl();
	}
	net_term();

	sceKernelExitGame();
	return 0;
}

//
// main thread
//
int main_thread( SceSize args, void *argp )
{
	// connect an access point.
	while( net_dialog() ) {
		net_not_connected();
	}

	pspDebugScreenInit();

	if( download_script() < 0 ) {
		sceKernelSleepThread();
		return 0;
	}

	main_menu();

	exit_eboot();
	return 0;
}


//
// callbacks
//
int exit_callback( int arg1, int arg2, void *common )
{
	exit_eboot();
	return 0;
}

int CallbackThread( SceSize args, void *argp )
{
	int cbid = sceKernelCreateCallback( "ExitCallback", exit_callback, NULL );
	sceKernelRegisterExitCallback( cbid );

	sceKernelSleepThreadCB();
	return 0;
}

int SetupCallbacks( void )
{
	int thid = sceKernelCreateThread( "update_thread", CallbackThread, 0x11, 0xFA0, 0, 0 );
	if( thid >= 0 ) {
		sceKernelStartThread( thid, 0, 0 );
	}
	return thid;
}

//
// Entry point.
//
int main( int argc, char **argv )
{
	DBG_INIT();
	SetupCallbacks();
	pspDebugScreenInit();
	sceCtrlSetSamplingMode( PSP_CTRL_MODE_DIGITAL );
	sceCtrlSetSamplingCycle( 0 );

	get_curdir( argv[0] );
	get_device_name( argv[0] );

	if( net_loadinit_module() < 0 ) {
		printf( "Error, could not load init module.\n" );
		sceKernelSleepThread();
		return 0;
	}

	SceUID thid = sceKernelCreateThread( "net_thread", main_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL );
	if( thid < 0 ) {
		printf( "Error, could not create thread.\n" );
		sceKernelSleepThread();
		return 0;
	}

	sceKernelStartThread( thid, 0, NULL );
	sceKernelExitDeleteThread( 0 );
	return 0;
}
